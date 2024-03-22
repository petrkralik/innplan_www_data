<?php


namespace businessObject;


/**
 * Represents a client entity.
 *
 * @property \businessObject\PropertyString $name
 * @property \businessObject\PropertyBool   $disabled
 */
class Client extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 */
	#[\Override] function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");
		return $this->apiUrlBase(). "/v1/client/{$this->id}";
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
		return $this->apiUrlBase(). "/v1/client/";
	}


}