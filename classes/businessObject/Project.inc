<?php


namespace businessObject;


class Project extends BusinessObject
{


	public int $id;


	/**
	 * @throws \iw\api\Exception
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


	#[\Override] function setProperty(string $propertyName, mixed $content): bool
	{
		// TODO: Implement setProperty() method.
	}


	#[\Override] function getProperty(string $propertyName): mixed
	{
		// TODO: Implement getProperty() method.
	}


}