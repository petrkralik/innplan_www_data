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


	function apiUrlCreate(): string
	{
		return urlBaseAPI."/v1/project/role";
	}


	/**
	 * @throws \businessObject\Exception
	 */
	function apiUrlGet(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI."/v1/project/role";
	}


	/**
	 * @throws Exception
	 */
	public function apiUrlEdit(): string
	{
		return $this->apiUrlGet();
	}


	/**
	 * @throws Exception
	 */
	public function apiUrlDelete(): string
	{
		return $this->apiUrlGet();
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