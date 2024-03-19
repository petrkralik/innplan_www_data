<?php


namespace businessObject;


class Project extends BusinessObject
{


	/**
	*/
	public function __construct(int $id)
	{
		parent::__construct();
		$this->id = $id;
		$this->initData();
	}


	#[\Override] function apiUriGet(): string
	{

		return "/v1/project/{$this->id}";
	}


	#[\Override] function properties(): array
	{

		return [
			"clientId"=> new Property(new PropertyInt(T, 1)),
			"client"=> new Property(new PropertyObjectReferral("clientId", "Client"))
		];
	}


}