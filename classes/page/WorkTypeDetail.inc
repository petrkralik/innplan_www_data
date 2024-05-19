<?php


namespace page;


class WorkTypeDetail extends Page2Columns
{


	private int $workTypeId;
	private \businessObject\WorkType $workType;


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \iw\dom\Exception
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
		}
		$e->append($this->dom->h2(N, $this->workType->name->getValue()));
		$data= [
				["popis", null],
				["seniorita", $this->workType->workTypeSeniorityId->getValue()],
				["uzamčeno", $this->workType->disabled->getValue()],
			];
		$e->append(new \iw\page\html\arrayDecorator\ArrayDecorator($this->dom, $data));

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