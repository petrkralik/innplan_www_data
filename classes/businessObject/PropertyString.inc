<?php


namespace businessObject;


class PropertyString extends PropertyType
{


	#[\Override] protected function setValueCheck(mixed $value): bool
	{
		if (is_string($value) || is_null($value))
			return \T;

		return \F;
	}


}