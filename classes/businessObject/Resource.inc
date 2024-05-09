<?php


namespace businessObject;


/**
 * Represents a Resource entity.
 *
 * @property PropertyString $name
 * @property PropertyBool   $disabled
 */
class Resource extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 */
	function apiUrlGet(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI."/v1/resource/{$this->id}";
	}


	function apiUrlCreate(): string
	{
		return urlBaseAPI."/v1/resource";
	}


	function propertyList(): array
	{
		return [
			"name"     => new PropertyString(),
			"disabled" => new PropertyBool(F, T),
		];
	}


	public function propertyListForCreation(): array
	{
		return $this->propertyList();
	}


}