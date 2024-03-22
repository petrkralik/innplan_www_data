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


	#[\Override] function apiUrl(): string
	{
		return "/v1/client/{$this->id}";
	}


	#[\Override] function propertyList(): array
	{
		return [
			"name"     => new PropertyString(),
			"disabled" => new PropertyBool(F, T),
		];
	}


}