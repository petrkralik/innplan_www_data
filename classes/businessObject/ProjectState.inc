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


	#[\Override] function apiUrl(): string
	{
		return "/v1/project/state/{$this->id}";
	}


	#[\Override] function propertyList(): array
	{
		return [
			"name"     => new PropertyString(),
			"disabled" => new PropertyBool(F, T),
		];
	}


}