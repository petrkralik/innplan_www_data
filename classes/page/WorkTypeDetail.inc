<?php


namespace page;


class WorkTypeDetail extends Page2Columns
{


	private int $workTypeId;
	private \businessObject\WorkType $workType;


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \iw\dom\Exception|\DOMException
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->workTypeId = $this->uriMatches[1];
		$e = $this->dom->div(
			N,
			$this->dom->h1(N, "detail typu práce")
		);
		$this->workType = new \businessObject\WorkType($this->workTypeId);
		try {
			$this->workType->loadData();
			$e->append($this->dom->h2(N, $this->workType->name->getValue()));
			$data = [
				["popis", null],
				["seniorita", $this->workType->workTypeSeniorityId->getValue()],
				["uzamčeno", $this->workType->disabled->getValue()],
				[null, [$this->buttonEdit(), $this->buttonDelete()]]
			];
			$e->append(new \iw\page\html\arrayDecorator\ArrayDecorator($this->dom, $data, [$this, "tableDataCallback"]));
		} catch (\businessObject\Exception $ex) {
			$e->append($this->domObjectLoadError());
		}


		return $e;
	}


	/**
	 * @throws \DOMException
	 */
	private function buttonEdit(): \iw\dom\Element
	{
		return $this->dom->a(
			N,
			urlBasePage. "/workType/{$this->workTypeId}/edit",
        	"upravit"
        );
	}


	/**
	 * @throws \DOMException
	 */
	private function buttonDelete(): \iw\dom\Element
	{
		return $this->dom->a(
			N,
			urlBasePage . "/workType/{$this->workTypeId}/delete",
			"smazat"
		);
	}


	public function tableDataCallback($row, $col, &$value): void
	{
		if ($row == 0 && $col == 1)
			$value = $value ?? "bez popisu";
		if ($row == 2 && $col == 1)
			$value = $value ? "ano" : "ne";
	}


	private function domObjectLoadError(): \iw\dom\Element
	{
		return $this->dom->p(
			[\iw\html::A_CLASS => "error"],
			"nepodařilo se najít, nebo nahrát data objektu"
		);
	}


}