<?php


namespace page;


class WorkTypeDetail extends Page2Columns
{


	private \businessObject\WorkType $workType;


	/**
	 * @throws \businessObject\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->workType= new \businessObject\WorkType($this->uriMatches[1]);
		$this->workType->loadData();
		return $this->dom->div();
	}


}