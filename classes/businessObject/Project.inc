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


	#[\Override] function loadData(): bool
	{
		// TODO: Implement loadData() method.
		echo "Load data of project {$this->id}";

		return T;
	}


}