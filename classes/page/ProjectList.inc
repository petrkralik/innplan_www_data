<?php


namespace page;


class ProjectList extends Page
{


	#[\Override] function setContent(\iw\dom\Element $body): void
	{
		$body->append("Project List");
	}


}