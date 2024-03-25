<?php


abstract class World extends iw\World_a
{


	protected APICall $api;


	function __construct()
	{
		$this->api = new APICall();
		parent::__construct();
	}


	/**
	 * Provides the base URL for the API endpoint. This method can be overridden in child classes
	 * to provide a different base URL if necessary.
	 *
	 * @return string The base URL for the API.
	 */
	function urlBaseApi(): string
	{
		return "https://api.innplan.westa.cz";
	}


	function urlBasePage(): string
	{
		return "https://innplan.westa.cz";
	}


}