<?php


namespace page\WorkType;


class WorkTypeList extends \page\Page2Columns
{



	private array $workTypes= [];


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 * @throws \iw\dom\Exception
	 * @throws \DOMException
	 * @throws \businessObject\property\Exception
	 * @throws \iw\table\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "workTypeList"],
			$this->dom->h1(\N, "seznam typů práce"),
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
			$this->dom->a(\N, \urlBasePage. "/workType/new", "nový typ práce")
		);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function init(): void
	{
		$result= $this->api->get(\urlBaseAPI. "/v1/workType");
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
	 * @throws \DOMException
	 */
	private function contentResourceList(): \iw\page\html\arrayDecorator\ArrayDecorator
	{
		$data= [["id", "název", "akce"]];
		foreach ($this->workTypes as $workType) {
			$data[]= [
				$workType->id,
				$this->dom->a(\N, \urlBasePage. "/workType/{$workType->id}", $workType->name->getValue()),
				$this->workTypeActions($workType)
			];
		}

        return new \iw\page\html\arrayDecorator\ArrayDecorator($data, flags: \iw\page\html\arrayDecorator\ArrayDecorator::HEADER_ROW);
	}


	/**
	 * @throws \DOMException
	 */
	private function workTypeActions(\businessObject\WorkType $workType): mixed
	{
		return [
			$this->dom->a(\N, \urlBasePage. "/workType/{$workType->id}/edit", "upravit"),
			$this->dom->a(\N, \urlBasePage. "/workType/{$workType->id}/delete", "smazat")
		];
	}


	private function contentNoResources(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "v seznamu nejsou žádné typy práce");
	}


}