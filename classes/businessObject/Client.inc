<?php


namespace businessObject;


/**
 * Represents a client entity.
 *
 * @property \businessObject\property\PropertyString $name
 * @property \businessObject\property\PropertyBool   $disabled
 */
class Client extends BusinessObject
{


	/**
	 * @throws Exception
	 */
	#[\Override] function apiUrlGet(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI."/v1/client/{$this->id}";
	}


	#[\Override] function propertyList(): array
	{
		return [
			"name"     => new \businessObject\property\PropertyString(),
			"disabled" => new \businessObject\property\PropertyBool(F, T),
		];
	}


	#[\Override] function apiUrlCreate(): string
	{
		return urlBaseAPI."/v1/client/";
	}


	#[\Override] public function propertyListForCreation(): array
	{
		return $this->propertyList();
	}


}