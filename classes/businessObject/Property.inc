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
	 * Indicates if the property has been set with an initial value.
	 * This flag is used to determine if the property has been initialized.
	 *
	 * @var bool
	 */
	private bool $isSet = false;

	/**
	 * Indicates if the property has been changed from its original value.
	 * This flag is used to track modifications to the property value.
	 *
	 * @var bool
	 */
	private bool $isChanged = false;


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
	 * Checks if the property has been set.
	 *
	 * @return bool Returns true if the property is set, false otherwise.
	 */
	public function isSet(): bool
	{
		return $this->isSet;
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
	 * Resets the change status of the property, effectively acknowledging the change.
	 */
	public function dropChange(): void
	{
		if ($this->isChanged) {
			unset($this->valueChanged);
			$this->isChanged = F;
		}
	}


	/**
	 * Erases the value of the property if it's not required. Throws an exception if
	 * trying to erase a required property.
	 *
	 * @throws Exception If the property is required and cannot be erased.
	 */
	public function erase(): void
	{
		if ($this->required)
			Error::PROPERTY_CANNOT_BE_ERASED->throw("Property cannot be erase as it is required.");
		unset($this->valueOriginal);
		unset($this->valueChanged);
		$this->isSet = F;
		$this->isChanged = F;
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
		// If the property is already set and the new value is the same as the old, there's no need to do anything
		if ($this->isSet() && ($this->getValue() === $value))
			return;

		// Validate the new value with custom check depending on each concrete property
		// If validation fails, an error is thrown
		if (!$this->valueCheckOnSet($value))
			Error::PROPERTY_TYPE_ERROR->throw("Property is not of required type");

		// If the property was previously set, store it as a changed value and mark the property as changed
		if ($this->isSet()) {
			$this->valueChanged = $value;
			$this->isChanged = T;

			// If the property was not previously set, store it as the original value and mark the property as set
		} else {
			$this->valueOriginal = $value;
			$this->isSet = true;
			echo "Set value ". $value;
		}

		// For each object that refers this property (referrals), we are going to remove the cached object value
		// Each referral knows how to assemble the object from the database based on the property's value
		// So, when the property changes, as it happened now, we need to clear the cached object to make sure the object
		// is reassembled with up-to-date data when it is requested next time.
		foreach ($this->getReferrals() as $referral)
			$referral->emptyObject();
	}


	/**
	 * Gets the current value of the property. Returns the changed value if there is one,
	 * otherwise the original value.
	 *
	 * @return mixed The current value of the property.
	 */
	public function getValue(): mixed
	{
		return $this->isChanged ? $this->valueChanged : $this->valueOriginal;
	}


	/**
	 * Gets the original value of the property.
	 *
	 * @return mixed The original value of the property.
	 */
	public function getValueOriginal(): mixed
	{
		return $this->valueOriginal;
	}


	/**
	 * Gets the changed value of the property if there is one.
	 *
	 * @return mixed The changed value of the property, or null if no change has been made.
	 */
	public function getValueChanged(): mixed
	{
		return $this->valueChanged;
	}


	/**
	 * Adds a PropertyObjectReferral instance to the list of referrals that reference this property.
	 * This method allows tracking of all PropertyObjectReferral instances that are linked to this property,
	 * enabling a bidirectional relationship between the property and its referrals.
	 *
	 * @param PropertyObjectReferral $referral The PropertyObjectReferral instance to add to the referrals list.
	 *
	 * @return void
	 */
	public function addReferral(PropertyObjectReferral $referral): void
	{
		$this->referrals[] = $referral;
	}


	/**
	 * Retrieves the list of all PropertyObjectReferral instances that reference this property.
	 * This method provides access to all referrals linked to this property, which can be useful
	 * for understanding the dependencies and relationships this property has with other business objects.
	 *
	 * @return array An array of PropertyObjectReferral instances that are linked to this property.
	 */
	public function getReferrals(): array
	{
		return $this->referrals;
	}


}