<?php

class APICall extends \iw\APICall {


	function __construct() {
		parent::__construct();
		$this-> headers[]= "Iw-Auth-Token: 280766b4-63fd-461b-b9e1-4fd7a71ac429";
	}


}
