<?php


namespace businessObject;


class Project extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 */
	public function __construct(int $id)
	{
		parent::__construct($id);
		$this->id = $id;
		$this->initData();
	}


	#[\Override] function apiUrl(): string
	{

		return "/v1/project/{$this->id}";
	}


	#[\Override] function propertyList(): array
	{

		return [
			"name"=> new PropertyString(),
			"dateStart"=> new PropertyDate(F, T),
			"dateEnd"=> new PropertyDate(F, T),
			"projectStateId"=> new PropertyInt(minimum: 1),
			"projectState"=> new PropertyObjectReferral("projectStateId", "ProjectState"),
			"clientId"=> new PropertyInt(minimum: 1),
			"client"=> new PropertyObjectReferral("clientId", "Client")
		];
	}


}