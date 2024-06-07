<?php


namespace page\WorkType;


abstract class WorkType extends \page\Page2Columns
{


	/**
	 * @var int The type ID of the work.
	 */
	private int $workTypeId;
	private \businessObject\WorkType $workType;
	private bool $workTypeIsLoaded= false;



	protected function getWorkTypeId(): int
	{
		if(!isset($this->workTypeId))
			$this->workTypeId= (int)$this->uriMatches[1];

		return $this->workTypeId;
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	protected function getBusinessObject(): \businessObject\WorkType
	{
		if(!isset($this->workType)) {
			$this->workType = new \businessObject\WorkType($this->getWorkTypeId());
			$this->workType->loadData();
		}

		return $this->workType;
	}






}