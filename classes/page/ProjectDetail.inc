<?php


namespace page;


class ProjectDetail extends Page2Columns
{


	private \businessObject\Project $project;


	#[\Override] function getContentMain(\iw\DOMElementExtension $element): void
	{
		// TODO: Implement getContentMain() method.
		$this->init();
	}

	private function init(): void
	{
		$this->project = new \businessObject\Project((int)$this->uriMatches[1]);
	}


}