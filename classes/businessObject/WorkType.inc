<?php


namespace businessObject;


/**
 * Represents a Work Type entity.
 *
 * @property \businessObject\property\PropertyString $name
 * @property \businessObject\property\PropertyInt    $workTypeSeniorityId
 * @property \businessObject\property\PropertyBool   $disabled
 * @property \businessObject\property\PropertyString $description
 */
class WorkType extends BusinessObject
{


	/**
	 * @throws Exception
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


	protected function propertyList(): array
	{
		return [
			\entity\WorkType::ATTRIBUTE_NAME         => new \businessObject\property\PropertyString(),
			\entity\WorkType::ATTRIBUTE_DESCRIPTION  => new \businessObject\property\PropertyString(false, true),
			\entity\WorkType::ATTRIBUTE_SENIORITY_ID => new \businessObject\property\PropertyInt(),
			\entity\WorkType::ATTRIBUTE_DISABLED     => new \businessObject\property\PropertyBool(false, true),
		];
	}


	protected function propertyListForCreation(): array
	{
		return $this->properties;
	}





}