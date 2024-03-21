<?php


namespace page;


/**
 * This class, ProjectDetail, is a subclass of Page2Columns.
 * It manages the details of a particular project.
 */
class ProjectDetail extends Page2Columns
{


	/**
	 * Declares a private variable $project of type \businessObject\Project.
	 * This variable is used to hold the instance of a project.
	 */
	private \businessObject\Project $project;


	/**
	 * This method 'fillContentMain' is used to generate the main content associated with the project.
	 * It takes an argument of type \iw\DOMElementExtension and returns void.
	 * The implementation of this method is yet to be defined.
	 *
	 * @return \iw\DOMElementExtension
	 */
	#[\Override] function getContentMain(): \iw\DOMElementExtension
	{
		$this->init();
		return $this->doc->div(N, "HAHAHAHA");
	}


	/**
	 * Private function 'init' is used to initialize the project object.
	 * This method takes no arguments and returns no value.
	 * It creates a new instance of \businessObject\Project and assigns it to $this->project.
	 *
	 * @return void
	 */
	private function init(): void
	{
		$this->project = new \businessObject\Project($this->uriMatches[1]);
	}


}