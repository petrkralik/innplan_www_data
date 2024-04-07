<?php


namespace page;


class WorkTypeNew extends Page2Columns
{


	private \iw\page\html\form\Form $form;


	function getContentMain(): ?\iw\dom\Element
	{
		//$this->buildForm();
		return $this->dom->div(
			[
				\iw\html::A_CLASS => "workTypeNew"
			],
			$this->dom->h1(N, "nový typ práce"),
			$this->buildForm()
		);
	}


	private function buildForm(): \iw\page\html\form\Form
	{
		$fid = "workTypeNewForm";
		$this->form = new \iw\page\html\form\Form(
			$this->dom,
			$fid,
			urlBasePage . "/workType/new/save",
			[$this, "formContent"],
			[]
		);
		$fName = new \iw\page\html\form\component\Text("{$fid}_name");
		$fName->size = 60;
		$this->form->addComponent($fName);

		return $this->form;
	}


	public function formContent()
	{
		return
			$this->dom->h2(N, "form content");
	}


	public function formHtmlContent(): array
	{
		return [
			$this->dom->h2(N, "form content")
		];
	}


}