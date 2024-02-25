<?php

abstract class World extends iw\World_a {


	public static ? \iw\cache\Cache				$_cache;


	function __construct() {
		parent::__construct();
		self::$_cache= & self::$_assets["cache"];
	}


}