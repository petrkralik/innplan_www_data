<?php


namespace businessObject;


class PropertyDate extends Property
{


	#[\Override] protected function valueCheckOnSet(mixed $value): bool
	{
		return T;
	}


}