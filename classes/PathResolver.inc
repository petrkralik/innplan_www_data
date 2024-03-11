<?php


class PathResolver extends \iw\Universe
{


	private string $requestUri;
	private static string $_defaultClass = "Home";
	private static array $_map = [
		"/\/abc\//i" => "abc"
	];


	function __construct()
	{
		parent::__construct();
		$this->requestUri = $_SERVER["REQUEST_URI"];
		$a= $this->getClass();
		var_dump($a);
	}


	function getClass(): ?string
	{
		foreach (self::$_map as $pattern => $className)
			if (preg_match($pattern, $this->requestUri))
				return $className;

		return self::$_defaultClass;
	}


}