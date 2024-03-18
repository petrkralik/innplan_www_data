<?php


namespace businessObject;


class PropertyObjectReferral extends PropertyType
{


	public readonly string $referredClassName;
	public readonly string $localForeignReferral;


	public function __construct(string $localForeignReferral, string $referredClassName)
	{
		parent::__construct();
		$this->localForeignReferral = $localForeignReferral;
		$this->referredClassName = $referredClassName;
	}


}