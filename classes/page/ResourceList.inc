<?php


namespace page;


class ResourceList extends Page2Columns
{


	private array $resources= [];


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "resourceList"],
			$this->dom->h1(N, "Seznam zdrojů"),
			$this->resources? $this->contentResourceList(): $this->contentNoResources()
		);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	private function init(): void
	{
		$result= $this->api->get(urlBaseAPI. "/v1/resource");
		if($result->statusCodeType== \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$resource= new \businessObject\Resource();
				$resource->apiResultMapData($data);
				$this->resources[]= $resource;
			}
		}
	}


	private function contentResourceList(): \iw\dom\Element
	{
		$e= $this->dom->div([\iw\html::A_CLASS=> "resource"]);
		foreach ($this->resources as $resource) {
			$e->append($this->contentResource($resource));
		}

		return $e;
	}


	private function contentNoResources(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "v seznamu nejsou žádné zdroje");
	}


	private function contentResource(\businessObject\Resource $resource): \iw\dom\Element
	{
		return $this->dom->div(
			[\iw\html::A_CLASS=> "resource"],
			$resource->name->getValue()
		);
	}



}