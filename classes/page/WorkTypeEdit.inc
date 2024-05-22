<?php


namespace page;


class WorkTypeEdit extends Page2Columns
{

	private \businessObject\WorkType $workType;
	private \iw\page\html\form\Form $form;
	private string $formId= "workTypeFormEdit";
	private int $workTypeId;


	function getContentMain(): ?\iw\dom\Element
	{
		$this->buildForm();
		return $this->dom->div(N, "Edit");
	}

	private function buildForm(): void
	{
		$this->form= new \iw\page\html\form\Form(
			$this->dom,
			$this->formId,
			urlBasePage. "/workType/{$this->workTypeId}/edit/save",
			[$this, "formOnGetContent"],
			[$this, "formOnSave"],
			null,
			null,
			null,
			[$this, "formOnSaveSuccess"],
			null
		);
	}


	private function getWorkTypeId(): int
	{
		return $this->workTypeId= (int)$this->uriMatches[1];
	}


	public function formOnGetContent(): mixed
	{
		return null;
	}


	public function formOnSave(): mixed
	{
		return null;
	}


	public function formOnSaveSuccess(): void
	{
		// code here
	}

	
}