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


	public const string PROPERTY_NAME= "name";
	public const string PROPERTY_SENIORITY_ID= "workTypeSeniorityId";
	public const string PROPERTY_DISABLED= "disabled";


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
			self::PROPERTY_NAME         => new PropertyString(),
			self::PROPERTY_SENIORITY_ID => new PropertyInt(),
			self::PROPERTY_DISABLED     => new PropertyBool(F, T),
		];
	}


	public function propertyListForCreation(): array
	{
		return $this->properties;
	}


}