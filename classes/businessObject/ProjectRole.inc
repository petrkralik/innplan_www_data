<?php


namespace businessObject;


use businessObject\Property\PropertyBool;
use businessObject\Property\PropertyString;


/**
 * Represents a Project role entity.
 *
 * @property PropertyString $name
 * @property PropertyBool   $disabled
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
			"name"     => new PropertyString(),
			"disabled" => new PropertyBool(F, T),
		];
	}


	public function propertyListForCreation(): array
	{
		return $this->propertyList();
	}


}