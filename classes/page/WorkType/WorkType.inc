<?php


namespace page\WorkType;


abstract class WorkType extends \page\Page2Columns
{


	/**
	 * @var int The type ID of the work.
	 */
	private int $workTypeId;


	protected function getWorkTypeId(): int
	{
		if(!isset($this->workTypeId))
			$this->workTypeId= (int)$this->uriMatches[1];

		return $this->workTypeId;
	}



}