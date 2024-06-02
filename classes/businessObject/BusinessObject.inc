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
	 * @var bool $dataInitiated Flag indicating whether the data for the business object has been initialized.
	 */
	public bool $dataInitiated = false;

	/**
	 * @var \businessObject\property\Property[] $properties Associative array storing properties of the business object, keyed by property names.
	 */
	protected array $properties;

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
	abstract protected function propertyList(): array;


	/**
	 * Method that should be implemented by descendants to specify
	 * which attributes are required for the create() method.
	 *
	 * @return array List of attribute names required for object creation.
	 */
	abstract protected function propertyListForCreation(): array;


	/**
	 * Constructor for the BusinessObject class. Initializes the object with a unique ID,
	 * sets up the properties by calling the abstract propertyList method, and initializes the API caller.
	 *
	 * @param int|null $id The unique identifier for the business object instance.
	 */
	public function __construct(?int $id = N)
	{
		parent::__construct();
		if ($id)
			$this->id = $id;
		$this->properties = $this->propertyList();
	}


	/**
	 * Creates a new instance of the business object by sending a POST request to the API.
	 * This method initializes the object with provided attributes, validates required properties,
	 * and handles the API response to set the object's ID and load its data.
	 *
	 * The method checks if the object already has an ID and throws an exception if it does,
	 * indicating that an existing object cannot be created again. It sets the object's attributes
	 * using the provided array and validates that all required properties for creation are set.
	 * After sending the POST request to the API, it checks the response status.
	 * If the response includes an ID, it sets the object's ID and loads the data from the response.
	 * If the ID is missing in the response, it throws an exception.
	 *
	 * @param   array|null  $attributes  Associative array of attributes to set on the object. The keys should
	 *                                   match the property names, and the values should be the property values.
	 *
	 * @return bool
	 * @throws Exception Throws an exception if the object already has an ID (indicating it exists),
	 *                   if a required property is not set, if the API call is unsuccessful,
	 *                   or if the API response does not include an ID for the newly created object.
	 * @throws \iw\api\Exception Throws an exception if the object already has an ID (indicating it exists),
	 * @throws \businessObject\property\Exception
	 *                   if a required property is not set, if the API call is unsuccessful,
	 *                   or if the API response does not include an ID for the newly created object.
	 */
	public function create(?array $attributes): bool
	{
		// Checking if the current object already has an ID assigned.
		// If an ID is already assigned, it means the object already exists.
		if (isset($this->id)) {

			// Throwing an exception as it will be an incorrect action
			// to attempt creating an existing object again.
			Error::CANNOT_CREATE->throw("Object of type ". $this::class. " cannot be created because it already exists.");
		}

		// Check if attributes are provided for creating the object.
		if ($attributes) {

			// If attributes are provided, then assign these attributes to the properties of
			// the object being created. This is done using the 'setAttributes' method
			// which matches up attribute values with the object's properties.
			$this->setAttributes($attributes);
		}

		// Here we start iterating over each property that’s required for object creation
		foreach ($this->propertyListForCreation() as $propertyName => $property) {

			// Checking if a property that has been marked as 'required' has been set or not.
			if ($property->required && !$property->isInitialized()) {

				// If a required property is not set, then throw an error.
				// As it is mandatory for all required properties to exist for successful object creation.
				Error::PROPERTY_NOT_SET->throw("The required property '$propertyName' is not set in object of type ". $this::class);
			}
		}

		// After all the required properties have been successfully set, we proceed with making a POST
		// request to the API to finally create the object.
		$response = $this->getApi()->post($this->apiUrlCreate(), $this->createCollectData());

		// Checking to see if the API call resulted in a successful response.
		if ($response->statusCodeType != \iw\HttpStatusCodeType::SUCCESS) {

			var_dump($response->body);
			// If the API call did not succeed, throw an error message that includes the HTTP status code.
			Error::API_DATA_POST->throw("Failed to create an object of type " . $this::class . " due to an error encountered by API. HTTP error code is {$response->statusCode->value}. Body:");
		}

		// Verify whether the API response includes an ID for the object that was created just now.
		if (isset($response->body->id)) {

			// If an ID was included in the API response, assign it to the object's ID property
			$this->id = $response->body->id;

			// Then proceed to load the rest of the data from the API response into
			// the corresponding properties of the object using the 'apiResultMapData' method.
			$this->apiResultMapData($response->body);

			// Lastly, we set the 'dataInitiated' flag to true to signify that the object’s
			// data has been imported and initialized.
			$this->dataInitiated = T;
		} else {

			// If an ID was NOT included in the API response after object creation,
			// throw an error because the ID is crucial for object identification and tracking.
			Error::API_RESPONSE_MISSING_ID->throw("The API response does not contain an 'id' for the new " . $this::class . " object that was expected to be created.");
		}

		return true;
	}


	/**
	 * Collects and prepares the data for the API request to create a new business object.
	 * This method iterates over the properties of the object and gathers their values,
	 * excluding any PropertyObjectReferral properties to avoid nested object complexity in the API call.
	 * The collected data is then used as the payload for the API request.
	 *
	 * For specific property types like PropertyDate, the method formats the value
	 * appropriately (e.g., converting a DateTime object to a string in Y-m-d format).
	 *
	 * @return array An associative array where each key is a property name and the value is the property's
	 *               value formatted for the API request. This array is used as the payload in the API call
	 *               to create or update the object.
	 * @throws Exception
	 * @throws \businessObject\property\Exception
	 */
	private function createCollectData(): array
	{
		$data = [];
		foreach ($this->propertyListForCreation() as $propertyName => $property)
			if (!$property instanceof PropertyObjectReferral && $property->isInitialized())
				$data[$propertyName] = match ($property::class) {
					\businessObject\property\PropertyDate::class => $property->getValue() ? $property->getValue()->format("Y-m-d") : N,
					default => $property->getValue()
				};

		return $data;
	}


	/**
	 * Sets the attributes of a business object based on a provided associative array.
	 * This method iterates over each entry in the array, where the key represents the property name
	 * and the value represents the value to be set for that property.
	 *
	 * @param   array  $attributes  Associative array of property names and values to be set.
	 *
	 * @throws Exception if the property does not exist or if the value is not valid for the property type.
	 * @throws \businessObject\property\Exception
	 */
	public function setAttributes(array $attributes): void
	{
		foreach ($attributes as $propertyName => $value) {

			// Check if the provided property name exists in the object properties
			if (! array_key_exists($propertyName, $this->properties)) {

				// Throw an error if the provided property does not exist
				Error::NONEXISTENT_PROPERTY->throw("Attribute '$propertyName' doesn't exist in the object ".$this::class);
			}

			// Check if the property is an instance of PropertyObjectReferral class
			if ($this->properties[$propertyName] instanceof PropertyObjectReferral) {

				// Throw an error if the provided property is an instance of PropertyObjectReferral class.
				// Such properties cannot be set directly, instead, their ID attribute should be set.
				Error::PROPERTY_TYPE_ERROR->throw("Attribute '$propertyName' cannot be set directly as it is a PropertyObjectReferral. Set its id directly in related attribute");
			}

			// Set the value of the property using the provided value
			$this->properties[$propertyName]->setValue($value);
		}
	}


	/**
	 * Magic getter method to access the value of a property dynamically.
	 * This method delegates the responsibility to the existing getProperty method.
	 *
	 * @param string $propertyName The name of the property to access.
	 *
	 * @return \businessObject\property\Property|BusinessObject The value of the requested property.
	 * @throws Exception|\businessObject\property\Exception If the property is not defined or cannot be accessed.
	 */
	public function __get(string $propertyName): \businessObject\property\Property|BusinessObject
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
	 * @throws Exception|\businessObject\property\Exception If the property is not defined or the value is invalid.
	 */
	public function __set(string $propertyName, mixed $value): void
	{
		$this->setProperty($propertyName, $value);
	}


	/**
	 * Identifies and returns a list of properties that have been changed.
	 * This method iterates over all properties of the business object and checks if any have been modified
	 * since their initial set value. Only properties that are instances of the Property class (or its descendants)
	 * and have their 'isChanged' method return true are considered changed.
	 *
	 * The method returns an associative array where each key is the name of a changed property, and the
	 * corresponding value is the Property object itself. This array can be used to further inspect changes,
	 * validate them, or update the object in the database or through an API.
	 *
	 * @return \businessObject\property\Property[] An associative array of changed properties. The keys are property names, and the values are
	 *               the new values for these properties.
	 */
	public function changes(): array
	{
		$changedProperties = [];
		foreach ($this->properties as $propertyName => $property)
			if ($property instanceof \businessObject\property\Property && $property->isChanged())
				$changedProperties[$propertyName] = $property;

		return $changedProperties;
	}


	/**
	 * Resets the list of changed properties. This method should be called after changes have been persisted,
	 * ensuring that the object reflects the current state without pending changes.
	 */
	public function dropChanges(): void
	{
		foreach ($this->properties as $property)
			if ($property instanceof \businessObject\property\Property)
				$property->dropChange();
	}


	/**
	 * Saves changes made to the properties to the database or via an API.
	 * This method should contain logic to persist the changes tracked in $changedProperties.
	 *
	 * @return bool Returns true if changes are successfully saved, false otherwise.
	 */
	public function saveChanges(): bool
	{
		$data= [];
		foreach ($this->properties as $name=>$property) {
			if($property->isChanged()) {
				echo "$name changed from '{$property->getValueOriginal()}' to '{$property->getValueChanged()}'". LF;
			}
		}
		return false;
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
		if ((!$this->dataInitiated || $forceLoad) && isset($this->id)) {
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
	 * @throws \businessObject\property\Exception
	 */
	private function loadDataFromAPI(): void
	{
		$response = $this->apiGet();
		if ($response->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			$this->apiResultMapData($response->body);
			$this->dataInitiated = true;
		} else
			Error::NO_OBJECT_LIKE_THIS->throw("Object loading error with http code {$response->statusCode->value}.");
	}


	/**
	 * Instantiates a new instance of the \iw\api\Call class and returns it.
	 *
	 * @return \APICall An instance of \iw\api\Call used to perform API calls.
	 */
	protected function getApi(): \APICall
	{
		return new \APICall();
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
		return $this->getApi()->get($this->apiUrlGet());
	}


	/**
	 * Maps the data from the API response to the object's properties. This method iterates over the response data
	 * and assigns the data to the respective properties of the object.
	 *
	 * @param \stdClass $body The response from the API containing the data.
	 *
	 * @throws Exception|\businessObject\property\Exception If there is an issue with setting the property values.
	 */
	public function apiResultMapData(\stdClass $body): void
	{
		foreach ($body as $property => $value)
			$this->setProperty($property, $value);
		$this->dataInitiated= true;
	}


	/**
	 * Sets the value of a property. This method checks if the property exists, validates the value,
	 * and sets the value while tracking any changes.
	 *
	 * @param string $propertyName The name of the property to set.
	 * @param mixed  $value        The value to set for the property.
	 *
	 * @throws Exception|\businessObject\property\Exception If the property does not exist or the value is not valid.
	 */
	public function setProperty(string $propertyName, mixed $value): void
	{
		if ($propertyName == "id") {
			if (!isset($this->id))
				$this->id = $value;
		} elseif (key_exists($propertyName, $this->properties)) {
			if ($this->properties[$propertyName] instanceof \businessObject\property\Property) {
				$value = match ($this->properties[$propertyName]::class) {
					\businessObject\property\PropertyDate::class => $this->convertValueStrToDate($value),
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


	/**
	 * Retrieves the Property object for a given property name. This method is used to access
	 * the Property object associated with a specific property of the business object.
	 *
	 * @param   string  $propertyName  The name of the property to retrieve.
	 *
	 * @return \businessObject\property\Property|BusinessObject The Property object associated with the given property name.
	 * @throws Exception If the property name is not registered in the object.
	 * @throws \businessObject\property\Exception
	 */
	public function getProperty(string $propertyName): \businessObject\property\Property|BusinessObject
	{
		if (!array_key_exists($propertyName, $this->properties))
			Error::NONEXISTENT_PROPERTY->throw("Property '$propertyName' isn't registered.");
		if (!$this->dataInitiated && isset($this->id))
			$this->loadData();

		return $this->getPropertyConverted($this->properties[$propertyName]);
	}


	/**
	 * @param   \businessObject\property\Property  $property
	 *
	 * @return \businessObject\property\Property|BusinessObject
	 * @throws \businessObject\property\Exception
	 */
	private function getPropertyConverted(\businessObject\property\Property $property): \businessObject\property\Property|BusinessObject
	{
		if ($property instanceof PropertyObjectReferral)
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


	/**
	 * @return \businessObject\property\Property[]
	 */
	public function getProperties(): array
	{
		return $this->properties;
	}


	/**
	 * @return \businessObject\property\Property[]
	 */
	public function getPropertiesForCreation(): array
	{
		return $this->propertyListForCreation();
	}


}