<?php


namespace businessObject;


use iw\Autoloader;

class Project extends BusinessObject
{


	public int $id;


	/**
	 * @throws \iw\APICallException
	 * @throws \iw\Exception
	 */
	public function __construct(int $id)
	{
		parent::__construct();
		$this->id= $id;
		$this->loadData();
	}


	/**
	 * @throws \iw\Exception
	 */
	#[\Override] function loadData(): bool
	{
		$result= $this-> api->get("https://api.innplan.westa.cz/v1/project/{$this->id}");
		var_dump($result->body);

		return T;
	}


}