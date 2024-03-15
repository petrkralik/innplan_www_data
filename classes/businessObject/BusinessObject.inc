<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	protected \iw\APICall $api;


	abstract function loadData(): bool;


	public function __construct() {
		parent::__construct();
		$this->api= new \iw\APICall();
	}


}