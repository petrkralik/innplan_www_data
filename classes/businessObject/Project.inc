<?php


namespace businessObject;


class Project extends BusinessObject
{


	public int $id;


	public function __construct(int $id)
	{
		parent::__construct();
		$this->id= $id;
		$this->loadData();
	}


	/**
	 * @throws \iw\APICallException
	 * @throws \iw\Exception
	 */
	#[\Override] function loadData(): bool
	{
		// TODO: Implement loadData() method.
		echo "Load data of project {$this->id}";
		$result= $this-> api->get("https://api.innplan.westa.cz/v1/project/{$this->id}");
		var_dump($result);
		return T;
	}


}