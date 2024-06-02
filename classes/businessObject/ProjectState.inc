<?php


namespace businessObject;


/**
 * Represents the state of a project.
 *
 * @property \businessObject\property\PropertyString $name
 * @property \businessObject\property\PropertyBool   $disabled
 *
 */
class ProjectState extends BusinessObject
{


	/**
	 */
	#[\Override] function apiUrlCreate(): string
	{
		return urlBaseAPI. "/project/state/";
	}


	/**
	 * @throws Exception
	 */
	#[\Override] function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI. "/v1/project/state/{$this->id}";
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


	#[\Override] function propertyList(): array
	{
		return [
			"name"     => new \businessObject\property\PropertyString(),
			"disabled" => new \businessObject\property\PropertyBool(F, T),
		];
	}


	/**
	 * @return array
	 */
	#[\Override] public function propertyListForCreation(): array
	{
		return $this->propertyList();
	}


}