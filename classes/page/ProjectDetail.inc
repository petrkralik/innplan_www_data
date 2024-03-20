<?php


namespace page;


class ProjectDetail extends Page2Columns
{


	private \businessObject\Project $project;


	/**
	 * @param   \iw\DOMElementExtension  $element
	 *
	 * @return void
	 * @throws \businessObject\Exception
	 * @throws \iw\api\Exception
	 */
	#[\Override] function getContentMain(\iw\DOMElementExtension $element): void
	{
		// TODO: Implement getContentMain() method.
		$this->init();
	}


	/**
	 * @throws \iw\api\Exception
	 * @throws \businessObject\Exception
	 */
	private function init(): void
	{
		$this->project = new \businessObject\Project((int)$this->uriMatches[1]);
		var_dump($this->project);
	}


}