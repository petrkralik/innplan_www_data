<?php


namespace page;


class ProjectStateList extends Page2Columns
{


	private array $projectStates;


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	#[\Override] function getContentMain(): \iw\dom\Element
	{
		$this->init();

		return $this->doc->div(
			[\iw\html::A_CLASS=> "projectStateList"],
			$this->doc->h1(\N, "Číselník stavů projektů"),
			$this->projectStates? $this->contentProjectStateList(): $this->contentNoProjects()
		);
	}


	private function contentProjectStateList(): \iw\dom\Element
	{
		$e = $this->doc->div([\iw\html::A_CLASS => "list"]);
		foreach ($this->projectStates as $projectState) {
			$e->append($this->contentProjectState($projectState));
		}

		return $e;
	}


	private function contentProjectState(\businessObject\ProjectState $projectState): \iw\dom\Element {
		$e = $this->doc->div(
			[\iw\html::A_CLASS=> "projectState"],
			$projectState->name->getValue()
		);

    	return $e;
	}


	private function contentNoProjects(): \iw\dom\Element
	{
		return $this->doc->div([\iw\html::A_CLASS => "noContentMessage"], "No project state found");
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	private function init(): void
	{
		$result = $this->api->get($this->urlBaseApi()."/v1/project/state");
		if ($result->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$project = new \businessObject\ProjectState();
				$project->apiResultMapData($data);
				$this->projectStates[] = $project;
			}
		}
	}


}