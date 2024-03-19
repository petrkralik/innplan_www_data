<?php


namespace businessObject;


class Project extends BusinessObject
{


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	public function __construct(int $id)
	{
		parent::__construct($id);
		$this->id = $id;
		$this->initData();
	}


	#[\Override] function apiUriGet(): string
	{

		return "/v1/project/{$this->id}";
	}


	#[\Override] function properties(): array
	{

		return [
			"name"=> new PropertyString(),
			"dateStart"=> new PropertyString(),
			"dateEnd"=> new PropertyString(),
			"clientId"=> new PropertyInt(minimum: 1),
			"client"=> new PropertyObjectReferral("clientId", "Client")
		];
	}


}