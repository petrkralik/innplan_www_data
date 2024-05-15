<?php


namespace page;


class ProjectStateList extends Page2Columns
{


	private array $projectStates; //This will hold the various states of project


	/**
	 * This function fetches main content of the project
	 * Initializes and returns the state of the project
	 *
	 * @throws \iw\api\Exception If there's a problem with making the API request
	 * @throws \businessObject\Exception If there's an exception on the business Object
	 * @throws \iw\dom\Exception If there's an exception with the dom
	 *
	 * @return \iw\dom\Element Returns the project state
	 */
	#[\Override] function getContentMain(): \iw\dom\Element
	{
		$this->init(); //Initialize the states

		//Return the project states
		return $this->dom->div([\iw\html::A_CLASS => "projectStateList"], $this->dom->h1(\N, "Číselník stavů projektů"),
			$this->projectStates ?$this->contentProjectStateList(): $this->contentNoProjects());
	}


	/**
	 * This function fetches the list of project states.
	 *
	 * @throws \iw\dom\Exception|\businessObject\Exception If there's any exception with the DOM while finding elements
	 * @return \iw\dom\Element Returns a div with list of project states.
	 */
	private function contentProjectStateList(): \iw\dom\Element
	{
		$e = $this->dom->div([\iw\html::A_CLASS => "list"]);
		foreach ($this->projectStates as $projectState) {
			$e->append($this->contentProjectState($projectState));
		}

		return $e;
	}


	/**
	 * This function fetches a particular project state.
	 *
	 * @param   \businessObject\ProjectState  $projectState  The state of the Project
	 *
	 * @return \iw\dom\Element Returns a div containing the project state
	 * @throws \businessObject\Exception
	 */
	private function contentProjectState(\businessObject\ProjectState $projectState): \iw\dom\Element
	{
		$e = $this->dom->div([\iw\html::A_CLASS => "projectState"], "#".$projectState->id." ".$projectState->name->getValue());

		return $e;
	}


	/**
	 * This function returns a div when there are no projects.
	 *
	 * @return \iw\dom\Element Returns a div with a message indicating no project states found
	 */
	private function contentNoProjects(): \iw\dom\Element
	{
		return $this->dom->div([\iw\html::A_CLASS => "noContentMessage"], "No project state found");
	}


	/**
	 * This function fetches the project states from the API and populates the projectStates array.
	 *
	 * @throws \iw\api\Exception If there's a problem while making API request
	 * @throws \businessObject\Exception If there's an exception from business Object
	 */
	private function init(): void
	{
		$result = $this->api->get(urlBaseAPI."/v1/project/state");
		if ($result->statusCodeType == \iw\HttpStatusCodeType::SUCCESS) {
			foreach ($result->body as $data) {
				$project = new \businessObject\ProjectState();
				$project->apiResultMapData($data);
				$this->projectStates[] = $project;
			}
		}
	}


}