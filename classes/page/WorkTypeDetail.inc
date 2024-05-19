<?php


namespace page;


class WorkTypeDetail extends Page2Columns
{


	private \businessObject\WorkType $workType;


	function getContentMain(): ?\iw\dom\Element
	{
		var_dump($this->uriMatches);
		return $this->dom->div();
	}


}