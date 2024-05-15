<?php


namespace businessObject;


/**
 * Represents a Project role entity.
 *
 * @property \businessObject\property\PropertyString $name
 * @property \businessObject\property\PropertyBool   $disabled
 */
class ProjectRole extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 */
	function apiUrlGet(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI."/v1/project/role";
	}


	function apiUrlCreate(): string
	{
		return urlBaseAPI."/v1/project/role";
	}


	function propertyList(): array
	{
		return [
			"name"     => new \businessObject\property\PropertyString(),
			"disabled" => new \businessObject\property\PropertyBool(F, T),
		];
	}


	public function propertyListForCreation(): array
	{
		return $this->propertyList();
	}


}