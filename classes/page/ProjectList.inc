<?php


namespace page;


class ProjectList extends Page2Columns
{


	/**
	 * @throws \iw\api\Exception
	 */
	#[\Override] function getContentMain(): \iw\dom\Element
	{
		$this->init();

		return $this->doc->h1(N, "Seznam projektů");
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	private function init(): void
	{
		$result = $this->api->get($this->urlBaseApi()."/v1/project");
		if($result->statusCodeType== \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$p = new \businessObject\Project();
				$p->apiResultMapData($data);
				var_dump($p);//echo $p->name->getValue(). LF;
				die();
			}
		}
	}


}