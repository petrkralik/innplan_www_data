<?php


namespace page;


class ProjectList extends Page2Columns
{


	#[\Override] function getContentMain(): \iw\dom\Element
	{
		return $this->doc->h1(N, "Seznam projektů");
	}


}