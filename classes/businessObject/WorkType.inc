<?php


namespace businessObject;


use businessObject\Property\PropertyString;


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
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI."/v1/workType/{$this->id}";
	}


	function apiUrlCreate(): string
	{
		return urlBaseAPI."/v1/workType";
	}


	function propertyList(): array
	{
		return [
			\entity\WorkType::ATTRIBUTE_NAME         => new PropertyString(),
			\entity\WorkType::ATTRIBUTE_SENIORITY_ID => new PropertyInt(),
			\entity\WorkType::ATTRIBUTE_DISABLED     => new PropertyBool(F, T),
		];
	}


	public function propertyListForCreation(): array
	{
		return $this->properties;
	}


}