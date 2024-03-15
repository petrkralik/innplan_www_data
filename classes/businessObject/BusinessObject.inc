<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	protected \APICall $api;


	abstract function loadData(): bool;


	public function __construct() {
		parent::__construct();
		$this->api= new \APICall();
	}


}