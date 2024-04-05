<?php


namespace page;


class RoleList extends Page2Columns
{


	private array $roles;


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "roleList"],
			$this->dom->h1(N, "Seznam projektových rolí"),
			$this->roles? $this->contentResourceList(): $this->contentNoResources()
		);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	private function init(): void
	{
		$result= $this->api->get(urlBaseAPI. "/v1/role");
		if($result->statusCodeType== \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$role= new \businessObject\ProjectRole();
				$role->apiResultMapData($data);
				$this->roles[]= $role;
			}
		}
	}


	private function contentResourceList(): \iw\dom\Element
	{
		$e= $this->dom->div([\iw\html::A_CLASS=> "projectRole"]);
		foreach ($this->roles as $role) {
			$e->append($this->contentResource($role));
		}

		return $e;
	}


	private function contentNoResources(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "v seznamu nejsou žádné projektové role");
	}


	private function contentResource(\businessObject\Resource $role): \iw\dom\Element
	{
		return $this->dom->div(
			[\iw\html::A_CLASS=> "projectRole"],
			$role->name->getValue()
		);
	}


}