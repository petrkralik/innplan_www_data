<?php


namespace businessObject;


/**
 * Represents the state of a project.
 *
 * @property PropertyString $name
 * @property PropertyBool   $disabled
 *
 */
class ProjectState extends BusinessObject
{


	/**
	 * @throws Exception
	 */
	#[\Override] function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");

		return $this->urlBaseApi(). "/v1/project/state/{$this->id}";
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
		return $this->urlBaseApi(). "/project/state/";
	}


	/**
	 * @return array
	 */
	#[\Override] public function propertyListForCreate(): array
	{
		return $this->propertyList();
	}


}