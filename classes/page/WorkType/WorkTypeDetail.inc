<?php


namespace page\WorkType;


class WorkTypeDetail extends WorkType
{


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \iw\dom\Exception|\DOMException
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->getWorkTypeId();
		$e = $this->dom->div(\N, $this->dom->h1(\N, "detail typu práce"));
		$workType = new \businessObject\WorkType($this->getWorkTypeId());
		try {
			$workType->loadData();
			$e->append($this->dom->h2(\N, $workType->name->getValue()));
			$data = [
				["id", $workType->id],
				["popis", $workType->description->getValue()],
				["seniorita", $workType->workTypeSeniorityId->getValue()],
				["uzamčeno", $workType->disabled->getValue()],
				[null, [$this->domButtonEdit(), $this->domButtonDelete()]],
			];
			$e->append(new \iw\page\html\arrayDecorator\ArrayDecorator($data, [$this, "tableDataCallback"]));
		} catch (\businessObject\Exception $ex) {
			$e->append($this->domObjectLoadError());
		}

		return $e;
	}


	/**
	 * @throws \DOMException
	 */
	private function domButtonEdit(): \iw\dom\Element
	{
		return $this->dom->a(\N, \urlBasePage. "/worktype/{$this->getWorkTypeId()}/edit", "editovat");
	}


	/**
	 * @throws \DOMException
	 */
	private function domButtonDelete(): \iw\dom\Element
	{
		return $this->dom->a(\N, \urlBasePage. "/worktype/{$this->getWorkTypeId()}/delete", 'smazat');
	}


	public function tableDataCallback($row, $col, &$value): void
	{
		if ($row == 1 && $col == 1)
			$value = $value ?? "bez popisu";
		if ($row == 3 && $col == 1)
			$value = $value ?"ano": "ne";
	}


	private function domObjectLoadError(): \iw\dom\Element
	{
		return $this->dom->p(
			[\iw\html::A_CLASS => "error"],
			"nepodařilo se najít, nebo nahrát data objektu"
		);
	}


}