<?php


namespace businessObject;


class PropertyDate extends Property
{


	#[\Override] protected function setValueCheck(mixed $value): bool
	{
		return T;
	}


}