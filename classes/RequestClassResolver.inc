<?php


class RequestClassResolver extends \iw\Universe
{


	private string $requestUri;
	private static string $_defaultClass = "\page\Home";
	private static array $_map = [
		"/\/project\/list\/?/i" => "\page\ProjectList",
	];


	/**
	 * @throws \RequestClassResolverException
	 */
	function __construct()
	{
		parent::__construct();
		$this->requestUri = $_SERVER["REQUEST_URI"];
		$a = $this->getClass();
		var_dump($a);
	}


	/**
	 * @throws \RequestClassResolverException
	 * @throws \ReflectionException
	 */
	function getClass(): \page\Page {
		$className= $this->getClassName();
		if(!class_exists($className))
			RequestClassResolverError::CLASS_NOT_EXISTS->throw("Class '$className' does not exist");
		$reflection= new ReflectionClass($className);
	}


	private function getClassName(): ?string
	{
		foreach (self::$_map as $pattern => $className) {
			if (preg_match($pattern, $this->requestUri)) {
				return $className;
			}
		}

		return self::$_defaultClass;
	}


}