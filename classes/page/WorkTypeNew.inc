<?php


namespace page;


class WorkTypeNew extends Page2Columns
{


	private \iw\page\html\form\Form $form;
	private string $formId = "workTypeNewForm";


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		//$this->buildForm();
		return $this->dom->div(
			[
				\iw\html::A_CLASS => "workTypeNew"
			],
			$this->dom->h1(N, "nový typ práce"),
			$this->form()
		);
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	private function form(): \iw\page\html\form\Form
	{
		$this->form = new \iw\page\html\form\Form(
			$this->dom,
			$this->formId,
			urlBasePage . "/workType/new/save",
			[$this, "formContent"]
		);
		$this->form->addComponent(new \iw\page\html\form\component\Text("{$this->formId}_name", N, [$this, "validateInputName"], null, 60));
		$this->form->addComponent(new \iw\page\html\form\component\Submit("{$this->formId}_submit", "zapsat"));
		return $this->form;
	}


	private function validateInputName(): bool
	{
		return T;
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	public function formContent(): \iw\dom\Element
	{
		return $this->dom->div(
			[
				\iw\html::A_CLASS => "formContent"
			],
			$this->dom->div(
				[\iw\html::A_CLASS => "formItem"],
				$this->dom->div([\iw\html::A_CLASS=> "title"], "název"),
				$this->dom->div([\iw\html::A_CLASS=> "input"], $this->form->getComponent($this->formId. "_name")),
				$this->dom->div([\iw\html::A_CLASS=> "submit", $this->form->getComponent($this->formId. "_submit")])
			)
		);
	}


}