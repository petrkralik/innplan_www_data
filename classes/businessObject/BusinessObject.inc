<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	protected \APICall $api;
	public bool $dataInitiated = F;
	protected array $propertiesData = [];
	protected array $properties = [];


	abstract function apiUriGet(): string;


	function apiUrlBase(): string
	{

		return "https://api.innplan.westa.cz";
	}


	public function __construct()
	{
		parent::__construct();
		$this->api = new \APICall();
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws Exception
	 */
	public function initData(bool $forceLoad = F): void
	{
		if (!$this->dataInitiated || $forceLoad)
			$this->initDataFromAPI();
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws Exception
	 */
	private function initDataFromAPI(): void
	{
		$response = $this->apiGet();
		if ($response->statusCodeType == \iw\HttpStatusCodeType::SUCCESS)
			$this->apiResultMapData($response);
		else
			Error::NO_OBJECT_LIKE_THIS->throw("Object loading error.");
	}


	/**
	 * @throws \iw\api\Exception
	 */
	protected function apiGet(): \iw\api\Response
	{

		return $this->api->get($this->apiUrlBase() . $this->apiUriGet());
	}


	protected function apiResultMapData(\iw\api\Response $response): void
	{
		foreach ($response->body as $property => $value)
			$this->setProperty($property, $value);
	}


	/**
	 * @throws Exception
	 */
	public function setProperty(string $propertyName, mixed $value): void
	{
		if (key_exists($propertyName, $this->properties))
			$this->properties[$propertyName] = $value;
		else
			Error::NONEXISTENT_PROPERTY->throw("Property '$propertyName' isn't registered.");
	}


	function getProperty(string $propertyName): mixed
	{
		// TODO: Implement getProperty() method.
	}


}