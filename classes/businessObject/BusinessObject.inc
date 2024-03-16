<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	protected \APICall $api;
	public bool $dataInitiated = F;


	abstract function apiUriGet(): string;


	abstract function setProperty(string $propertyName, mixed $content): bool;


	abstract function getProperty(string $propertyName): mixed;


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
			$this->apiMapAttributes($response);
		else
			Error::NO_OBJECT_LIKE_THIS->throw("Object loading error");
	}


	/**
	 * @throws \iw\api\Exception
	 */
	protected function apiGet(): \iw\api\Response
	{

		return $this->api->get($this->apiUrlBase() . $this->apiUriGet());
	}


	protected function apiMapAttributes(\iw\api\Response $response): bool
	{

		return T;
	}


}