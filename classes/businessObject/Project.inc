<?php


namespace businessObject;


class Project extends BusinessObject
{


	public int $id;


	public function __construct(int $id)
	{
		parent::__construct();
		$this->id = $id;
	}


	#[\Override] function apiUriGet(): string
	{

		return "/v1/project/{$this->id}";
	}


	#[\Override] function setProperty(string $propertyName, mixed $content): bool
	{
		// TODO: Implement setProperty() method.
	}


	#[\Override] function getProperty(string $propertyName): mixed
	{
		// TODO: Implement getProperty() method.
	}


}