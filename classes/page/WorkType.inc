<?php


namespace page;


abstract class WorkType extends Page2Columns
{


	/**
	 * @var int The type ID of the work.
	 */
	protected int $workTypeId;


	protected function getWorkTypeId(): int
	{
		if(!isset($this->workTypeId))
			$this->workTypeId= (int)$this->uriMatches[1];

		return $this->workTypeId;
	}



}