<?php


namespace page;


class ClientList extends Page2Columns
{


	private array $clients= [];


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	#[\Override] function getContentMain(): \iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "clientList"],
			$this->dom->h1(\N, "Seznam klientů"),
			$this->clients? $this->contentClientList(): $this->contentNoClients()
		);
	}


	private function contentClientList(): \iw\dom\Element
	{
		$e = $this->dom->div([\iw\html::A_CLASS => "list"]);
		foreach ($this->clients as $project) {
			$e->append($this->contentClient($project));
		}

		return $e;
	}


	private function contentClient(\businessObject\Client $client): \iw\dom\Element {
		$e = $this->dom->div(
			[\iw\html::A_CLASS=> "client"],
			$client->name->getValue()
		);

    	return $e;
	}


	private function contentNoClients(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "No clients found");
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	private function init(): void
	{
		$result = $this->api->get(urlBasePage."/v1/client");
		if ($result->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$project = new \businessObject\Client();
				$project->apiResultMapData($data);
				$this->clients[] = $project;
			}
		}
	}


}