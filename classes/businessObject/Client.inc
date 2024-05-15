<?php


namespace businessObject;


use businessObject\Property\PropertyBool;
use businessObject\Property\PropertyString;


/**
 * Represents a client entity.
 *
 * @property PropertyString $name
 * @property PropertyBool   $disabled
 */
class Client extends BusinessObject
{


	/**
	 * @throws Exception
	 */
	#[\Override] function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");
		return urlBaseAPI. "/v1/client/{$this->id}";
	}


	#[\Override] function propertyList(): array
	{
		return [
			"name"     => new PropertyString(),
			"disabled" => new PropertyBool(F, T),
		];
	}


	#[\Override] function apiUrlCreate(): string
	{
		return urlBaseAPI. "/v1/client/";
	}


	#[\Override] public function propertyListForCreation(): array
	{
		return $this->propertyList();
	}


}