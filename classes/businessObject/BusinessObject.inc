<?php


namespace businessObject;


use iw\api\Exception;

abstract class BusinessObject extends \World
{


	protected \APICall $api;


	abstract function initData(): bool;
	abstract function urlGet(): string;


	public function __construct() {
		parent::__construct();
		$this->api= new \APICall();
	}


	/**
	 * @throws Exception
	 */
	protected function get(): array
	{
		$result= $this->api->get($this->urlGet());
		return N;
	}


}