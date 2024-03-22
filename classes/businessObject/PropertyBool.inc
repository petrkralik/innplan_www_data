<?php


namespace businessObject;


class PropertyBool extends Property
{



	#[\Override] protected function setValueCheck(mixed $value): bool
	{
		if((($value=== N) && ($this->nullable)) || is_bool($value))
			return T;

		return F;
	}


}