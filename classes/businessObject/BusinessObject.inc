<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	protected \APICall $api;
	public bool $dataInitiated = F;
	private array $properties;
	public int $id;
	private array $changedProperties= [];
	private bool $inLoadProgress= F;


	abstract function apiUrl(): string;


	abstract function propertyList(): array;


	public function changes(): array
	{
		return $this->changedProperties;
	}


	public function dropChanges(): void
	{
		$this->changedProperties= [];
	}


	public function saveChanges(): void
	{
		//foreach ($this->changedProperties as $propertyName=> $value) {
			//$this->
		//}
	}


	public function __construct(int $id)
	{
		parent::__construct();
		$this->id = $id;
		$this->properties = $this->propertyList();
		$this->api = new \APICall();
	}


	function apiUrlBase(): string
	{
		return "https://api.innplan.westa.cz";
	}


	/**
	 * @throws Exception
	 */
	public function initData(bool $forceLoad = F): void
	{
		if (! $this->dataInitiated || $forceLoad)
			try {
				$this->initDataFromAPI();
			}
			catch(\iw\api\Exception $ex) {
				Error::API_DATA_LOAD->throw("API data load error", previous: $ex);
			}
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws Exception
	 */
	private function initDataFromAPI(): void
	{
		$response = $this->apiGet();
		if ($response->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			$this->apiResultMapData($response);
			$this->dataInitiated = T;
		} else
			Error::NO_OBJECT_LIKE_THIS->throw("Object loading error with http code {$response->statusCode->value}.");
	}


	/**
	 * @throws \iw\api\Exception
	 */
	protected function apiGet(): \iw\api\Response
	{
		return $this->api->get($this->apiUrlBase().$this->apiUrl());
	}


	/**
	 * @throws \businessObject\Exception
	 */
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
		if ($propertyName != "id") {
			if (key_exists($propertyName, $this->properties)) {
				if ($this->properties[$propertyName] instanceof Property) {
					switch ($this->properties[$propertyName]::class) {
						case PropertyDate::class:
							$this->properties[$propertyName]->set($this->convertValueStrToDate($value));
							break;
						default:
							$this->properties[$propertyName]->set($value);
					}
				} else {
					Error::ITEM_MUST_BE_INSTANCE_OF_PROPERTY->throw("Item must be instance of 'Property'.");
				}
			} else {
				Error::NONEXISTENT_PROPERTY->throw("Property '$propertyName' isn't registered.");
			}
		}
	}


	/**
	 * @throws \businessObject\Exception
	 */
	private function convertValueStrToDate(?string $value): ?\DateTime {
		if($value=== N)
			return N;
		if (!$this->strDateWellFormed($value))
			Error::PROPERTY_TYPE_ERROR->throw("Value content of 'date' malformed");
		$dateTime = \DateTime::createFromFormat("Y-m-d H:i:s", "$value 00:00:00");
		if ($dateTime === false)
			Error::PROPERTY_TYPE_ERROR->throw("Failed to create DateTime object from the provided value");

		return $dateTime;
	}


	private function strDateWellFormed(string $value): bool
	{
		$matches = [];
		if (preg_match("/^(\d{4})-(\d{2})-(\d{2})$/", $value, $matches)) {
			$year = (int)$matches[1];
			$month = (int)$matches[2];
			$day = (int)$matches[3];
			if ($year < 1000 || $year > 9999)
				return F;
			if ($month < 1 || $month > 12)
				return F;
			if ($day < 1 || $day > cal_days_in_month(CAL_GREGORIAN, $month, $year))
				return F;

			return T;
		}

		return F;
	}


}