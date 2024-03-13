<?php


/**
 * The RequestClassResolver class determines and instantiates the appropriate class based on the request URI.
 * It extends the base Universe class, providing a dynamic page handling mechanism for the application.
 * By leveraging the RequestClassResolverUriMapper, it decouples the URI resolution logic, enhancing modularity and maintainability.
 */
class RequestClassResolver extends \iw\Universe
{


	/**
	 * The current request URI used to determine the corresponding class to instantiate.
	 * This property is initialized from the $_SERVER global variable, reflecting the current HTTP request.
	 */
	private string $requestUri;


	/**
	 * Constructor initializes the class and sets the current request URI.
	 * The constructor ensures that the request URI is captured at the time of object instantiation, providing a snapshot of the request state.
	 */
	public function __construct()
	{
		parent::__construct();
		$this->requestUri = $_SERVER["REQUEST_URI"];
	}


	/**
	 * Retrieves and instantiates the appropriate page class based on the current URI.
	 * This method utilizes the RequestClassResolverUriMapper to determine the class to instantiate and its constructor arguments.
	 *
	 * @param   DocumentProvider  $documentProvider  A provider for any necessary documents or dependencies required by the page class.
	 *
	 * @return \page\Page An instance of the determined page class, ready for use.
	 * @throws \ReflectionException If there is an error during the class reflection process.
	 * @throws \RequestClassResolverException If the determined class does not exist or is of the incorrect type.
	 */
	public function getPageClass(DocumentProvider $documentProvider): \page\Page
	{
		$info = RequestClassResolverUriMapper::_getClassInfo($this->requestUri);
		$className = $info["className"];
		$matches = $info["matches"];

		return $this->getReflection($className)->newInstanceArgs([$documentProvider, $matches]);
	}


	/**
	 * Creates a reflection of the specified class.
	 * This method checks if the class exists and is a subclass of the expected parent class, providing dynamic type safety.
	 *
	 * @param   string  $className  The name of the class to reflect.
	 *
	 * @return ReflectionClass A reflection of the class, used for dynamic instantiation.
	 * @throws \RequestClassResolverException If the class is not a subclass of the expected parent.
	 * @throws \ReflectionException If the class does not exist.
	 */
	private function getReflection(string $className): ReflectionClass
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


}
