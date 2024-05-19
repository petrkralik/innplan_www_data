<?php


namespace page;


class WorkTypeDetail extends Page2Columns
{


	private \businessObject\WorkType $workType;


	function getContentMain(): ?\iw\dom\Element
	{
		$this->workType= new \businessObject\WorkType($this->uriMatches[1]);
		return $this->dom->div();
	}


}