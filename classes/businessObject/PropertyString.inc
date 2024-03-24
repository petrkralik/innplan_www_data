<?php


namespace businessObject;


class PropertyString extends Property
{


	#[\Override] protected function valueCheckOnSet(mixed $value): bool
	{
		if (is_string($value) || is_null($value))
			return \T;

		return \F;
	}


}