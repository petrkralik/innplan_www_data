<?php


namespace page;


class ProjectList extends Page2Columns
{


	private array $projects;


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	#[\Override] function getContentMain(): \iw\dom\Element
	{
		$this->init();

		return $this->dom->div(
			[\iw\html::A_CLASS=> "projectList"],
			$this->dom->h1(N, "Seznam projektů"),
			$this->projects? $this->contentProjectList(): $this->contentNoProjects()
		);
	}


	private function contentProjectList(): \iw\dom\Element
	{
		$e = $this->dom->div([\iw\html::A_CLASS => "list"]);
		foreach ($this->projects as $project) {
			$e->append($this->contentProject($project));
		}

		return $e;
	}


	private function contentProject(\businessObject\Project $project): \iw\dom\Element {
		$e = $this->dom->div(
			[\iw\html::A_CLASS=> "project"],
			$project->name->getValue()
		);

    	return $e;
	}


	private function contentNoProjects(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "No project's found");
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	private function init(): void
	{
		$result = $this->api->get($this->urlBaseApi()."/v1/project");
		if ($result->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$project = new \businessObject\Project();
				$project->apiResultMapData($data);
				$this->projects[] = $project;
			}
		}
	}


}