<?php


class PathResolver extends \iw\Universe
{


	private string $requestUri;


	function __construct()
	{
		parent::__construct();
		$this->requestUri= $_SERVER["REQUEST_URI"];
	}


	function getClass()
	{

	}


	private function parsePath() {

	}


}