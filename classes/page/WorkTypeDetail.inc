<?php


namespace page;


class WorkTypeDetail extends Page2Columns
{


	private int $workTypeId;
	private \businessObject\WorkType $workType;


	/**
	 * @throws \businessObject\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->workTypeId= $this->uriMatches[1];
		$e= $this->dom->div(
			N,
			$this->dom->h1(N, "detail typu práce")
		);
		$this->workType= new \businessObject\WorkType($this->workTypeId);
		try {
			$this->workType->loadData();
		}
		catch (\businessObject\Exception $ex) {
			$e->append($this->domObjectLoadError());
			throw $ex;
		}
		return $e;
	}


	private function domObjectLoadError(): \iw\dom\Element
	{
		return $this->dom->p(
			[\iw\html::A_CLASS=> "error"],
			"nepodařilo se najít, nebo nahrát data objektu"
		);
	}


}