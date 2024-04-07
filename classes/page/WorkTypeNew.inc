<?php


namespace page;


class WorkTypeNew extends Page2Columns
{


	private \iw\page\html\form\Form $form;
	private string $formId = "workTypeNewForm";


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


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	private function buildForm(): \iw\page\html\form\Form
	{
		$this->form = new \iw\page\html\form\Form(
			$this->dom,
			$this->formId,
			urlBasePage . "/workType/new/save",
			[$this, "formContent"]
		);
		$fName = new \iw\page\html\form\component\Text("{$this->formId}_name");
		$fName->size = 60;
		$this->form->addComponent($fName);

		return $this->form;
	}


	public function formContent(): \iw\dom\Element
	{
		return $this->dom->div(
			[
				\iw\html::A_CLASS => "formContent"
			],
			$this->dom->div(
				[\iw\html::A_CLASS => "formItem"],
				$this->dom->div([\iw\html::A_CLASS=> "title"], "název"),
				$this->dom->div([\iw\html::A_CLASS=> "input"], $this->form->getComponent($this->formId. "_name"))
			)
		);
	}


}