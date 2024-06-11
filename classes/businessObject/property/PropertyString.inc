<?php


namespace businessObject\property;


/**
 * PropertyString is a subclass of Property specifically designed to handle string values.
 * It includes validation to ensure that the value set is indeed a string or null, based on the property's configuration.
 */
class PropertyString extends Property
{


	/**
	 * Validates the provided value to ensure it is a string. If the property is set to nullable,
	 * it also allows null values.
	 *
	 * @param mixed $value The value to be checked.
	 *
	 * @return bool Returns true if the value is a string or null (when nullable is allowed); otherwise, false.
	 */
	protected function valueCheckOnSet(mixed &$value): bool
	{
		if (is_string($value) || ($this->nullable && is_null($value)))
			return true;

		return false;
	}


}
