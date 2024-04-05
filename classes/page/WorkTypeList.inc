<?php


namespace page;


class WorkTypeList extends Page2Columns {



	private array $workTypes= [];


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "workTypeList"],
			$this->dom->h1(N, "seznam typů práce"),
			$this->workTypes? $this->contentResourceList(): $this->contentNoResources()
		);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	private function init(): void
	{
		$result= $this->api->get(urlBaseAPI. "/v1/workType");
		if($result->statusCodeType== \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$workType= new \businessObject\WorkType();
				$workType->apiResultMapData($data);
				$this->workTypes[]= $workType;
			}
		}
	}


	private function contentResourceList(): \iw\dom\Element
	{
		$e= $this->dom->div([\iw\html::A_CLASS=> "workTypes"]);
		foreach ($this->workTypes as $resource) {
			$e->append($this->contentResource($resource));
		}

		return $e;
	}


	private function contentNoResources(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "v seznamu nejsou žádné typy práce");
	}


	private function contentResource(\businessObject\WorkType $workType): \iw\dom\Element
	{
		return $this->dom->div(
			[\iw\html::A_CLASS=> "workType"],
			$workType->name->getValue()
		);
	}



}