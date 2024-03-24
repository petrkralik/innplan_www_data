<?php


namespace businessObject;


/**
 * PropertyBool is a specialized version of Property designed to handle boolean values.
 * It ensures that only valid boolean values (or null if nullable) are set to the property.
 */
class PropertyBool extends Property
{


	/**
	 * Validates the provided value to ensure it is a boolean or null (if nullable is allowed).
	 * This method overrides the valueCheckOnSet method in the base Property class to provide
	 * specific validation for boolean values.
	 *
	 * @param mixed $value The value to be checked.
	 *
	 * @return bool Returns true if the value is a boolean or null (when nullable is allowed); otherwise, false.
	 */
	#[\Override] protected function valueCheckOnSet(mixed $value): bool
	{
		if ((($value === N) && ($this->nullable)) || is_bool($value))
			return T;

		return F;
	}


}