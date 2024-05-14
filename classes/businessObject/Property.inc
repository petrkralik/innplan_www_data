<?php


namespace businessObject;


/**
 * Abstract class Property serves as a base for different types of properties in a business object.
 * It manages the original and potentially changed values of a property, tracks if a property is set,
 * and whether it has been changed.
 */
abstract class Property
{


	public readonly string $id;


	/**
	 * @var PropertyObjectReferral[] An array of PropertyObjectReferral instances that reference this property.
	 * This array allows the property to keep track of all PropertyObjectReferral instances that are linked to it,
	 * facilitating a clear understanding of how this property is referenced throughout the business object model.
	 */
	private array $referrals = [];

	/**
	 * The original value of the property before any changes.
	 * This value is used to track changes and revert to the initial state if necessary.
	 *
	 * @var mixed
	 */
	private mixed $valueOriginal;

	/**
	 * The new value of the property if it has been changed.
	 * This value is used to track the current state of the property if any changes have been made.
	 *
	 * @var mixed
	 */
	private mixed $valueChanged;

	/**
	 * Indicates if the property is required.
	 * If true, the property must be set to a valid value, and cannot be erased or left uninitialized.
	 *
	 * @var bool
	 */
	public readonly bool $required;

	/**
	 * Indicates if the property can be set to null.
	 * If false, the property must have a non-null value.
	 *
	 * @var bool
	 */
	public readonly bool $nullable;

	/**
	 * Indicates if the property has been changed from its original value.
	 * This flag is used to track modifications to the property value.
	 *
	 * @var bool
	 */
	private bool $isChanged = false;

	/**
	 * This flag denotes if the property has been initialized.
	 *
	 * @var bool
	 */
	private bool $isInitialized = false;


	/**
	 * Abstract method to validate the value on set. Must be implemented by subclasses
	 * to define how the value is validated.
	 *
	 * @param mixed $value The value to check.
	 *
	 * @return bool Returns true if the value is valid, false otherwise.
	 */
	abstract protected function valueCheckOnSet(mixed $value): bool;


	/**
	 * Constructs a new Property instance with specified requirements.
	 *
	 * @param bool $required Specifies if the property is required.
	 * @param bool $nullable Specifies if the property can be null.
	 */
	public function __construct(bool $required = T, bool $nullable = F)
	{
		$this->id = uniqid();
		$this->required = $required;
		$this->nullable = $nullable;
	}


	/**
	 * Checks if the property has been initialized.
	 *
	 * @return bool Returns true if the property has been initialized, false otherwise.
	 */
	public function isInitialized(): bool
	{
		return $this->isInitialized;
	}


	/**
	 * Checks if a property has been initialized. If not, an exception is thrown.
	 *
	 * @throws \businessObject\Exception If the property has not been initialized.
	 */
	private function checkInitialization(): void
	{
		if (! $this->isInitialized)
			Error::PROPERTY_NOT_INITIALIZED->throw("Property is not initialized.");
	}


	/**
	 * Checks if the property value has been changed.
	 *
	 * @return bool Returns true if the property has been changed, false otherwise.
	 */
	public function isChanged(): bool
	{
		return $this->isChanged;
	}


	/**
	 * Resets the change status of the property. Empties the changed value and sets the changed
	 * flag to false, effectively acknowledging the change.
	 *
	 * Used to revert the property to its original state.
	 */
	public function dropChange(): void
	{
		if ($this->isChanged) {
			unset($this->valueChanged);
			$this->isChanged = false;
		}
	}


	/**
	 * Erases the value of the property if it's not required. Throws an exception if
	 * trying to erase a required property.
	 *
	 * @throws Exception If the property is required and cannot be erased.
	 */
	public function clear(): void
	{
		if ($this->required)
			Error::PROPERTY_CANNOT_BE_ERASED->throw("Property cannot be erase as it is required.");
		unset($this->valueOriginal);
		unset($this->valueChanged);
		$this->isInitialized = false;
		$this->isChanged = false;
	}


	/**
	 * This method is used to initialize the property with a value. It also sets the isInitialized
	 * and isChanged flags. If the property is already initialized, it will throw an exception.
	 *
	 * @param   mixed  $value  The value to initialize the property with.
	 *
	 * @return void
	 * @throws \businessObject\Exception If the property is already initialized.
	 *
	 */
	public function initialize(mixed $value): void
	{
		if ($this->isInitialized)
			Error::PROPERTY_ALREADY_INITIALIZED->throw("Property already initialized.");
		$this->valueOriginal = $value;
		$this->isInitialized = true;
		unset($this->valueChanged);
		$this->isChanged = false;
	}


	/**
	 * Sets the value of the property, checking its validity with valueCheckOnSet.
	 * If the property has been previously set, it marks the property as changed.
	 *
	 * @param mixed $value The new value to set.
	 *
	 * @throws Exception If the value is not valid according to valueCheckOnSet.
	 */
	public function setValue(mixed $value): void
	{
		// If the property has not been initialized
		if (! $this->isInitialized) {

			// Initialize it with the provided value
			$this->initialize($value);

			// Exit the function to avoid additional processing
			return;
		}

		// If the property is already initialized and the new value is identical to the old value,
		// then there is no need to make any changes. Therefore, we return from the function.
		if ($this->getValue() === $value)
			return;

		// Verify the new value against custom checks, based on the specific implementation of each property.
		// If the validation fails, it indicates that the new value does not adhere to the required type for this property,
		// hence an error is thrown.
		if (! $this->valueCheckOnSet($value))
			Error::PROPERTY_TYPE_ERROR->throw("Property is not of required type");

		// Assign the new value to the 'valueChanged' field. This signifies that the property has been updated
		// with a new value (which was verified to be of the correct type in the previous step).
		$this->valueChanged = $value;

		// Update 'isChanged' status, setting it to true, indicating that the property has been modified.
		$this->isChanged = T;

		// Loop through each object that refers to this property (referrals).
		// Each referral contains information about how to build the object from the database,
		// based on the value of this property.
		// So, when this property changes, as is the case now, we need to clear the cached object data for each referral.
		// This ensures that the next time the object is needed, it will be reconstructed with the most up-to-date data.
		foreach ($this->getReferrals() as $referral) {
			$referral->emptyObject();
		} // Clear existing cached data
	}


	/**
	 * Gets the current value of the property. Returns the changed value if there is one,
	 * otherwise the original value.
	 *
	 * @return mixed The current value of the property.
	 * @throws \businessObject\Exception
	 */
	public function getValue(): mixed
	{
		$this->checkInitialization();

		return $this->isChanged ? $this->valueChanged : $this->valueOriginal;
	}


	/**
	 * Gets the original value of the property.
	 *
	 * @return mixed The original value of the property.
	 * @throws \businessObject\Exception
	 */
	public function getValueOriginal(): mixed
	{
		$this->checkInitialization();

		return $this->valueOriginal;
	}


	/**
	 * Gets the changed value of the property if there is one.
	 *
	 * @return mixed The changed value of the property, or null if no change has been made.
	 * @throws \businessObject\Exception
	 */
	public function getValueChanged(): mixed
	{
		$this->checkInitialization();

		return $this->valueChanged;
	}


	/**
	 * Adds a PropertyObjectReferral instance to the list of referrals that reference this property.
	 * This method allows tracking of all PropertyObjectReferral instances that are linked to this property,
	 * enabling a bidirectional relationship between the property and its referrals.
	 *
	 * @param   PropertyObjectReferral  $referral  The PropertyObjectReferral instance to add to the referrals list.
	 *
	 * @return void
	 * @throws \businessObject\Exception
	 */
	public function addReferral(PropertyObjectReferral $referral): void
	{
		$this->checkInitialization();

		$this->referrals[] = $referral;
	}


	/**
	 * Retrieves the list of all PropertyObjectReferral instances that reference this property.
	 * This method provides access to all referrals linked to this property, which can be useful
	 * for understanding the dependencies and relationships this property has with other business objects.
	 *
	 * @return array An array of PropertyObjectReferral instances that are linked to this property.
	 * @throws \businessObject\Exception
	 */
	public function getReferrals(): array
	{
		$this->checkInitialization();

		return $this->referrals;
	}


}