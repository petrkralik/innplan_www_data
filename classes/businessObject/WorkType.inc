<?php


namespace businessObject;




/**
 * Represents a Work Type entity.
 *
 * @property \businessObject\property\PropertyString $name
 * @property \businessObject\property\PropertyBool $disabled
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


	function propertyList(): array
	{
		return [
			\entity\WorkType::ATTRIBUTE_NAME         => new \businessObject\property\PropertyString(),
			\entity\WorkType::ATTRIBUTE_SENIORITY_ID => new \businessObject\property\PropertyInt(),
			\entity\WorkType::ATTRIBUTE_DISABLED     => new \businessObject\property\PropertyBool(F, T),
		];
	}


	public function propertyListForCreation(): array
	{
		return $this->properties;
	}


}