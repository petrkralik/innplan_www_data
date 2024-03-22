<?php


namespace businessObject;


/**
 * Represents the state of a project.
 *
 * @property \businessObject\PropertyString $name
 * @property \businessObject\PropertyBool   $disabled
 *
 */
class ProjectState extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 */
	#[\Override] function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");
		return "/v1/project/state/{$this->id}";
	}


	#[\Override] function propertyList(): array
	{
		return [
			"name"     => new PropertyString(),
			"disabled" => new PropertyBool(F, T),
		];
	}


	#[\Override] function apiUrlCreate(): string
	{
		return $this->apiUrlBase(). "/project/state/";
	}


}