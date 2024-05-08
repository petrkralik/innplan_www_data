<?php


namespace businessObject;


/**
 * Represents a Work Type entity.
 *
 * @property PropertyString $name
 * @property PropertyBool   $disabled
 */
class WorkType extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 */
	function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI . "/v1/workType/{$this->id}";
	}


	function apiUrlCreate(): string
	{
		return urlBaseAPI . "/v1/workType";
	}


	function propertyList(): array
	{
		return [
			"name" => new PropertyString(),
			"workTypeSeniorityId"=> new PropertyInt(),
			"disabled" => new PropertyBool(F, T),
		];
	}


	public function propertyListForCreate(): array
	{
		return $this->propertyList();
	}


}