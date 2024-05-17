<?php


namespace page;


class WorkTypeList extends Page2Columns {



	private array $workTypes= [];


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 * @throws \iw\dom\Exception
	 * @throws \DOMException
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "workTypeList"],
			$this->dom->h1(N, "seznam typů práce"),
			$this->linkCreateNew(),
			$this->workTypes? $this->contentResourceList(): $this->contentNoResources()
		);
	}


	/**
	 * @throws \DOMException
	 */
	private function linkCreateNew(): \iw\dom\Element {
		return $this->dom->div(
			[
				\iw\html::A_CLASS=> "workTypeNewLink",
				\iw\html::A_ID=> "workTypeNewLink",
			],
			$this->dom->a(N, urlBasePage. "/workType/new", "nový typ práce")
		);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 * @throws \businessObject\property\Exception
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


    /**
     * @throws \iw\dom\Exception
     * @throws \iw\table\Exception
     * @throws \businessObject\property\Exception
     */
	private function contentResourceList(): \iw\page\html\TableDecorator
	{
        $t= new \iw\table\Table();
        $t->addField("id");
        $t->addField("název");
        $t->addField("akce");
		$e= $this->dom->div([\iw\html::A_CLASS=> "workTypes"]);
		foreach ($this->workTypes as $workType)
            $t->addRow($workType->id, $workType->name->getValue(), null);

        return new \iw\page\html\TableDecorator($this->dom, $t);
	}


	private function contentNoResources(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "v seznamu nejsou žádné typy práce");
	}


}