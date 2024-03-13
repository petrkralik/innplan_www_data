<?php


class RequestClassResolver extends \iw\Universe
{


	private string $requestUri;
	private static string $_landingPage = "\page\Home";
	private static array $_map = [
		"/\/project\/list\/?/i" => "\page\ProjectList",
		"/\/project\/(\d+)\/detail\/?/i" => "\page\ProjectDetail",
	];


	/**
	 * @throws \RequestClassResolverException
	 * @throws \ReflectionException
	 */
	function __construct()
	{
		parent::__construct();
		$this->requestUri = $_SERVER["REQUEST_URI"];
	}


	/**
	 * @throws \RequestClassResolverException
	 * @throws \ReflectionException
	 */
	function getPageClass(DocumentProvider $documentProvider): \page\Page
	{
		$info = $this->getClassInfo();

		return $this->getReflection($info["className"])->newInstanceArgs([$documentProvider, $info["matches"]]);
	}


	/**
	 * @throws \ReflectionException
	 * @throws \RequestClassResolverException
	 */
	private function getReflection($className): ReflectionClass
	{
		if (! class_exists($className)) {
			RequestClassResolverError::CLASS_NOT_EXISTS->throw("Class '$className' does not exist");
		}
		$reflection = new ReflectionClass($className);
		if (! $reflection->isSubclassOf(\page\Page::class)) {
			RequestClassResolverError::CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT->throw("Class must be successor of the parent '".\page\Page::class."'");
		}

		return $reflection;
	}


	private function getClassInfo(): ?array
	{
		$resultantClass = N;
		$matches = [];
		foreach (self::$_map as $pattern => $className) {
			if (preg_match($pattern, $this->requestUri, $matches)) {
				$resultantClass = $className;
				break;
			}
		}

		return [
			"className" => $resultantClass ?? self::$_landingPage,
			"matches"   => $matches,
		];
	}


}