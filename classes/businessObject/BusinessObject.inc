<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	protected \APICall $api;
	public bool $dataInitiated = F;
	private array $properties;
	public int $id;


	abstract function apiUriGet(): string;


	abstract function properties(): array;


	public function __construct(int $id)
	{
		parent::__construct();
		$this->id = $id;
		$this->properties = $this->properties();
		$this->api = new \APICall();
	}


	function apiUrlBase(): string
	{
		return "https://api.innplan.westa.cz";
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws Exception
	 */
	public function initData(bool $forceLoad = F): void
	{
		if (! $this->dataInitiated || $forceLoad)
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
			$this->apiResultMapData($response); else
			Error::NO_OBJECT_LIKE_THIS->throw("Object loading error.");
	}


	/**
	 * @throws \iw\api\Exception
	 */
	protected function apiGet(): \iw\api\Response
	{
		return $this->api->get($this->apiUrlBase().$this->apiUriGet());
	}


	/**
	 * @throws \businessObject\Exception
	 */
	protected function apiResultMapData(\iw\api\Response $response): void
	{
		foreach ($response->body as $property => $value) {
			$this->setProperty($property, $value);
		}
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
		echo $value. LF;
		if($value=== N)
			return N;
		if (!$this->strDateWellFormed($value))
			Error::PROPERTY_TYPE_ERROR->throw("Value content of 'date' malformed");
		$dateTime = \DateTime::createFromFormat("Y-m-d", $value);
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