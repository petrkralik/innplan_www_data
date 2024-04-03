<?php


/**
 * The World class is an abstract foundation for all main application components, providing
 * essential methods and properties for API interaction and service management. It inherits
 * from the iw\World_a class, which includes additional base functionalities required
 * throughout the application.
 *
 * The World class introduces a structured way to manage services and API calls, ensuring
 * consistency and reusability across different parts of the application. It uses a service
 * locator pattern to centrally manage service instances, which aids in the decoupling of
 * component dependencies.
 */
class World extends iw\World_a
{


	/**
	 * A static instance of the service locator. This static locator allows services to be
	 * registered and accessed globally within the application, providing a centralized
	 * point for service management.
	 */
	private static \iw\service\locator\Locator $_serviceLocator;


	private static self $_instance;


	/**
	 * Constructor for the World class. Initializes the API call handler to facilitate
	 * API interactions throughout the application. The constructor ensures that each
	 * instance of the derived class has access to the APICall functionality.
	 */
	function __construct()
	{
		parent::__construct();
	}


	/**
	 * Gets the singleton instance of the World class. If the instance doesn't exist, it will be created.
	 *
	 * @return World The singleton instance of the World class.
	 */
	public static function getInstance(): self
	{
		if (!isset(self::$_instance))
			self::$_instance = new self();

		return self::$_instance;
	}


	public static function _serviceLocator(): \iw\service\locator\Locator
	{
		if(!isset(self::$_serviceLocator))
			self::$_serviceLocator= new \iw\service\locator\Locator();

		return self::$_serviceLocator;
	}


	public function serviceLocator(): \iw\service\locator\Locator
	{
		return self::_serviceLocator();
	}


}