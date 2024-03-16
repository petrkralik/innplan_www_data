<?php


namespace businessObject;


class Project extends BusinessObject
{


	public int $id;


	/**
	 * @throws \iw\Exception
	 */
	public function __construct(int $id)
	{
		parent::__construct();
		$this->id = $id;
		$this->initData();
	}


	/**
	 * @throws \iw\Exception
	 */
	#[\Override] function initData(): bool
	{
		$this->get();

		return T;
	}


	#[\Override] function urlGet(): string
	{

		return "https://api.innplan.westa.cz/v1/project/{$this->id}";
	}


}