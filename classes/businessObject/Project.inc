<?php


namespace businessObject;


class Project extends BusinessObject
{


	protected array $properties = [
		"clientId"=> []
	];


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


}