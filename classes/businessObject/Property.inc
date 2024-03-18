<?php


namespace businessObject;


class Property
{


	public readonly PropertyType $type;


	public function __construct(PropertyType $type)
	{
		$this->type = $type;
	}


}