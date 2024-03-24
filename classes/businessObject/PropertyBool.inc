<?php


namespace businessObject;


class PropertyBool extends Property
{



	#[\Override] protected function valueCheckOnSet(mixed $value): bool
	{
		if((($value=== N) && ($this->nullable)) || is_bool($value))
			return T;

		return F;
	}


}