<?php


namespace businessObject;


/**
 * Abstract class BusinessObject serves as a base class for all business entities within the application.
 * It provides common functionalities such as API interactions and property management.
 * This class extends a generic World class, providing a foundation for specific business object implementations.
 */
abstract class BusinessObject extends \World
{


	/**
	 * @var \APICall $api An instance of APICall to handle API requests, facilitating communication with external services.
	 */
	protected \APICall $api;

	/**
	 * @var bool $dataInitiated Flag indicating whether the data for the business object has been initialized.
	 */
	public bool $dataInitiated = false;

	/**
	 * @var array $properties Associative array storing properties of the business object, keyed by property names.
	 */
	private array $properties;

	/**
	 * @var int|null $id Unique identifier for the business object, essential for database operations and API interactions.
	 */
	public readonly ?int $id;


	/**
	 * Abstract method that should return the specific API endpoint URL for the business object.
	 * Implementing classes must define this to interact with the correct API endpoint.
	 *
	 * @return string The API endpoint URL specific to the business object.
	 */
	abstract function apiUrlGet(): string;


	abstract function apiUrlCreate(): string;


	/**
	 * Abstract method that should return a list of properties associated with the business object.
	 * Implementing classes must define this to ensure the business object has its required properties.
	 *
	 * @return array An array of property definitions for the business object.
	 */
	abstract function propertyList(): array;


	/**
	 * Constructor for the BusinessObject class. Initializes the object with a unique ID,
	 * sets up the properties by calling the abstract propertyList method, and initializes the API caller.
	 *
	 * @param   int|null  $id  The unique identifier for the business object instance.
	 */
	public function __construct(?int $id= N)
	{
		parent::__construct();
		$this->id= $id;
		$this->properties = $this->propertyList();
		$this->api = new \APICall();
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	public function create(array $attributes): void
	{
		if($this->id)
			Error::CANNOT_CREATE->throw("Object of ". $this::class. " cannot be created because it exists.");
		$this->setAttributes($attributes);
		foreach ($this->properties as $propertyName => $property)
			if ($property->required && !$property->isSet())
				Error::PROPERTY_NOT_SET->throw("Required property '$propertyName' is not set in object of " . $this::class);
		$response = $this->api->post($this->apiUrlCreate(), $this->createCollectData());
		if ($response->statusCodeType != \iw\HttpStatusCodeType::SUCCESS) {
			var_dump($response->body);
			Error::API_DATA_POST->throw("Failed to create object of " . $this::class . " due to API error {$response->statusCode->value}.");
		}
	}


	private function createCollectData(): array
	{
		$data = [];
		foreach ($this->properties as $propertyName => $property)
			if (!$property instanceof PropertyObjectReferral && $property->isSet())
				$data[$propertyName] = match ($property::class) {
					PropertyDate::class=> $property->getValue()? $property->getValue()->format("Y-m-d"): N,
					default=> $property->getValue()
				};

		return $data;
	}


	/**
	 * Sets the attributes of a business object based on a provided associative array.
	 * This method iterates over each entry in the array, where the key represents the property name
	 * and the value represents the value to be set for that property.
	 *
	 * @param array $attributes Associative array of property names and values to be set.
	 * @throws Exception if the property does not exist or if the value is not valid for the property type.
	 */
	public function setAttributes(array $attributes): void
	{
		foreach ($attributes as $propertyName => $value) {
			if (!array_key_exists($propertyName, $this->properties))
				Error::NONEXISTENT_PROPERTY->throw("Attribute '$propertyName' doesn't exist in the object ". $this::class);
			if ($this->properties[$propertyName] instanceof PropertyObjectReferral)
				Error::PROPERTY_TYPE_ERROR->throw("Attribute '$propertyName' cannot be set directly as it is a PropertyObjectReferral. Set its id directly in related attribute");
			$this->properties[$propertyName]->setValue($value);
		}
	}


	/**
	 * Magic getter method to access the value of a property dynamically.
	 * This method delegates the responsibility to the existing getProperty method.
	 *
	 * @param   string  $propertyName  The name of the property to access.
	 *
	 * @return \businessObject\Property|\businessObject\BusinessObject The value of the requested property.
	 * @throws \businessObject\Exception If the property is not defined or cannot be accessed.
	 */
	public function __get(string $propertyName): Property|BusinessObject
	{
		return $this->getProperty($propertyName);
	}


	/**
	 * Magic setter method to set the value of a property dynamically.
	 * This method delegates the responsibility to the existing setProperty method.
	 *
	 * @param string $propertyName The name of the property to set.
	 * @param mixed  $value        The value to set to the property.
	 *
	 * @throws Exception If the property is not defined or the value is invalid.
	 */
	public function __set(string $propertyName, mixed $value): void
	{
		$this->setProperty($propertyName, $value);
	}


	/**
	 * Retrieves a list of properties that have been changed.
	 * This method can be used to identify which properties need to be updated in the database or via an API.
	 *
	 * @return array An array of changed properties.
	 */
	public function changes(): array
	{
		return [];
	}


	/**
	 * Resets the list of changed properties. This method should be called after changes have been persisted,
	 * ensuring that the object reflects the current state without pending changes.
	 */
	public function dropChanges(): void
	{

	}


	/**
	 * Saves changes made to the properties to the database or via an API.
	 * This method should contain logic to persist the changes tracked in $changedProperties.
	 *
	 * @return bool Returns true if changes are successfully saved, false otherwise.
	 */
	public function saveChanges(): bool
	{
		// @todo Logic to save changes goes here.
		return T;
	}


	/**
	 * Provides the base URL for the API endpoint. This method can be overridden in child classes
	 * to provide a different base URL if necessary.
	 *
	 * @return string The base URL for the API.
	 */
	function apiUrlBase(): string
	{
		return "https://api.innplan.westa.cz";
	}


	/**
	 * Initializes the object's data from the API. If data has not been loaded or a force reload is requested,
	 * this method fetches the data from the API and maps it to the object's properties.
	 *
	 * @param bool $forceLoad Forces the reload of data even if it has already been loaded.
	 *
	 * @throws Exception If there is an issue with data loading.
	 */
	public function loadData(bool $forceLoad = false): void
	{
		if (!$this->dataInitiated || $forceLoad && $this->id) {
			try {
				$this->loadDataFromAPI();
			} catch (\iw\api\Exception $ex) {
				Error::API_DATA_LOAD->throw("API data load error", previous: $ex);
			}
		}
	}


	/**
	 * Private method to initialize data from the API. It makes an API call, checks the response,
	 * and maps the data to the object's properties if the call is successful.
	 *
	 * @throws \iw\api\Exception If the API call fails.
	 * @throws Exception If the response status code is not successful.
	 */
	private function loadDataFromAPI(): void
	{
		$response = $this->apiGet();
		if ($response->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			$this->apiResultMapData($response);
			$this->dataInitiated = true;
		} else {
			Error::NO_OBJECT_LIKE_THIS->throw("Object loading error with http code {$response->statusCode->value}.");
		}
	}


	/**
	 * Protected method to perform a GET request to the object's API endpoint. It constructs the full URL
	 * by combining the base URL with the endpoint specific to the object.
	 *
	 * @return \iw\api\Response The response from the API.
	 * @throws \iw\api\Exception If the API request fails.
	 */
	protected function apiGet(): \iw\api\Response
	{
		return $this->api->get($this->apiUrlGet());
	}


	/**
	 * Maps the data from the API response to the object's properties. This method iterates over the response data
	 * and assigns the data to the respective properties of the object.
	 *
	 * @param \iw\api\Response $response The response from the API containing the data.
	 *
	 * @throws Exception If there is an issue with setting the property values.
	 */
	protected function apiResultMapData(\iw\api\Response $response): void
	{
		foreach ($response->body as $property => $value) {
			$this->setProperty($property, $value);
		}
	}


	/**
	 * Sets the value of a property. This method checks if the property exists, validates the value,
	 * and sets the value while tracking any changes.
	 *
	 * @param string $propertyName The name of the property to set.
	 * @param mixed  $value        The value to set for the property.
	 *
	 * @throws Exception If the property does not exist or the value is not valid.
	 */
	public function setProperty(string $propertyName, mixed $value): void
	{
		if ($propertyName != "id") {
			if (key_exists($propertyName, $this->properties)) {
				if ($this->properties[$propertyName] instanceof Property) {
					$value = match ($this->properties[$propertyName]::class) {
						PropertyDate::class => $this->convertValueStrToDate($value),
						default => $value
					};
					$this->properties[$propertyName]->setValue($value);
				} else {
					Error::ITEM_MUST_BE_INSTANCE_OF_PROPERTY->throw("Item must be instance of 'Property'.");
				}
			} else {
				Error::NONEXISTENT_PROPERTY->throw("Property '$propertyName' isn't registered.");
			}
		}
	}


	/**
	 * Retrieves the Property object for a given property name. This method is used to access
	 * the Property object associated with a specific property of the business object.
	 *
	 * @param   string  $propertyName  The name of the property to retrieve.
	 *
	 * @return \businessObject\Property|\businessObject\BusinessObject The Property object associated with the given property name.
	 * @throws \businessObject\Exception If the property name is not registered in the object.
	 */
	public function getProperty(string $propertyName): Property|BusinessObject
	{
		if (!array_key_exists($propertyName, $this->properties))
			Error::NONEXISTENT_PROPERTY->throw("Property '$propertyName' isn't registered.");
		if (!$this->dataInitiated && $this->id)
			$this->loadData();

		return $this->getPropertyConverted($this->properties[$propertyName]);
	}


	/**
	 * @param   \businessObject\Property  $property
	 *
	 * @return \businessObject\Property|\businessObject\BusinessObject
	 */
	private function getPropertyConverted(Property $property): Property|BusinessObject
	{
		if($property instanceof PropertyObjectReferral)
			return $property->getObject();
		else
			return $property;
	}


	/**
	 * Converts a string value to a DateTime object if the string is properly formatted.
	 * This method is specifically used for properties of type PropertyDate.
	 *
	 * @param ?string $value The string value to convert.
	 *
	 * @return ?\DateTime The converted DateTime object or null if the input is null or improperly formatted.
	 * @throws Exception If the string is not a well-formed date.
	 */
	private function convertValueStrToDate(?string $value): ?\DateTime
	{
		if ($value === N)
			return N;
		if (!$this->strDateWellFormed($value))
			Error::PROPERTY_TYPE_ERROR->throw("Value content of 'date' malformed");
		$dateTime = \DateTime::createFromFormat("Y-m-d H:i:s", "$value 00:00:00");
		if ($dateTime === false)
			Error::PROPERTY_TYPE_ERROR->throw("Failed to create DateTime object from the provided value");

		return $dateTime;
	}


	/**
	 * Validates whether a string is a well-formed date string in the format 'Y-m-d'.
	 *
	 * @param string $value The date string to validate.
	 *
	 * @return bool True if the string is a well-formed date, false otherwise.
	 */
	private function strDateWellFormed(string $value): bool
	{
		$matches = [];
		if (preg_match("/^(\d{4})-(\d{2})-(\d{2})$/", $value, $matches)) {
			[$year, $month, $day] = array_map('intval', array_slice($matches, 1));

			return checkdate($month, $day, $year);
		}

		return false;
	}


}