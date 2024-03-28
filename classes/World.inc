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
abstract class World extends iw\World_a
{


	/**
	 * A constant identifier for the document service within the service locator.
	 * This identifier is used to retrieve the specific service instance from the service locator.
	 */
	public const string SERVICE_DOC = "serviceDoc";

	/**
	 * An APICall instance used for conducting API interactions. This property allows
	 * derived classes to easily make API requests without instantiating their own APICall objects.
	 */
	protected APICall $api;

	/**
	 * A static instance of the service locator. This static locator allows services to be
	 * registered and accessed globally within the application, providing a centralized
	 * point for service management.
	 */
	private static \iw\service\locator\Locator $_serviceLocator;


	/**
	 * Constructor for the World class. Initializes the API call handler to facilitate
	 * API interactions throughout the application. The constructor ensures that each
	 * instance of the derived class has access to the APICall functionality.
	 */
	function __construct()
	{
		parent::__construct();
		$this->api = new APICall();
	}


	/**
	 * Registers the necessary static services with the service locator. This method is
	 * responsible for setting up application-wide services that are available throughout
	 * the application's lifecycle.
	 *
	 * @throws \iw\service\locator\Exception
	 */
	private static function _setStaticServices(): void
	{
		self::_getServiceLocator()->registerService(
			self::SERVICE_DOC,
			"\iw\dom\Document",
			N,
			function (): \iw\dom\Document {
				return new \iw\dom\Document();
			}
		);
	}


	/**
	 * Ensures the static service locator is instantiated and available for use. If the
	 * service locator has not been initialized, this method will create it and register
	 * the static services.
	 *
	 * @throws \iw\service\locator\Exception
	 */
	public static function _setupServiceLocator(): void
	{
		if (!isset(self::$_serviceLocator)) {
			echo "Setup Service Locator";
			self::$_serviceLocator = new \iw\service\locator\Locator();
			self::_setStaticServices();
		}
	}


	/**
	 * Sets the service locator for instance-level use. This method wraps the static
	 * _setServiceLocator method, ensuring that the service locator is ready for use
	 * at the instance level.
	 *
	 * @throws \iw\service\locator\Exception
	 */
	public function setServiceLocator(): void
	{
		self::_setupServiceLocator();
	}


	/**
	 * Retrieves the static service locator instance, initializing it if necessary.
	 * This method provides access to the service locator from both static and instance
	 * contexts, allowing services to be registered and retrieved.
	 *
	 * @return \iw\service\locator\Locator The service locator instance.
	 * @throws \iw\service\locator\Exception
	 */
	public static function _getServiceLocator(): \iw\service\locator\Locator
	{
		self::_setupServiceLocator();

		return self::$_serviceLocator;
	}


	/**
	 * Retrieves the service locator instance for the current object. This instance-level
	 * method provides a convenient way to access the service locator without needing to
	 * reference the class statically.
	 *
	 * @return \iw\service\locator\Locator The service locator instance.
	 * @throws \iw\service\locator\Exception
	 */
	public function getServiceLocator(): \iw\service\locator\Locator
	{
		return self::_getServiceLocator();
	}


	/**
	 * Provides the base URL for API endpoints. This method can be overridden in derived
	 * classes to specify different base URLs for different components or environments.
	 *
	 * @return string The base URL for API requests.
	 */
	function urlBaseApi(): string
	{
		return "https://api.innplan.westa.cz";
	}


	/**
	 * Provides the base URL for the page. This method can be similarly overridden in
	 * derived classes to specify alternative base URLs for different parts of the application.
	 *
	 * @return string The base URL for the page.
	 */
	function urlBasePage(): string
	{
		return "https://innplan.westa.cz";
	}


}