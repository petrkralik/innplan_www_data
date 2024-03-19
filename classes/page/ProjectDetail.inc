<?php


namespace page;


class ProjectDetail extends Page2Columns
{


	private \businessObject\Project $project;


	/**
	 * @throws \iw\api\Exception
	 */
	#[\Override] function getContentMain(\iw\DOMElementExtension $element): void
	{
		// TODO: Implement getContentMain() method.
		$this->init();
	}


	/**
	 * @throws \iw\api\Exception
	 */
	private function init(): void
	{
		$this->project = new \businessObject\Project((int)$this->uriMatches[1]);
	}


}