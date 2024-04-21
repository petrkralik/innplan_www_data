<?php


namespace page;


class WorkTypeNew extends Page2Columns
{


	private const string ACTION_NEW = "ACTION_NEW";
	private const string ACTION_SAVE = "ACTION_SAVE";


	private \iw\page\html\form\Form $form;
	private string $formId = "workTypeNewForm";


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->buildForm();
		if ($this->detectProcess() == self::ACTION_SAVE)
			$this->save();

		return $this->dom->div(
			[
				\iw\html::A_CLASS => "workTypeNew"
			],
			$this->dom->h1(N, "nový typ práce"),
			$this->form
		);
	}


	/**
	 * @throws \iw\page\html\form\component\Exception
	 */
	private function save(): void
	{
		if (!$this->form->validate()) {
			foreach ($this->form->componentIterator() as $component) {
				if ($component->onError)
					foreach ($component->errors as $error) {
						echo $error->message . LF;
					}
			}
		}
	}


	function detectProcess(): string
	{
		return match ($this->uriMatches[1]) {
			"new" => self::ACTION_NEW,
			"save" => self::ACTION_SAVE
		};
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	private function buildForm(): void
	{
		$this->form = new \iw\page\html\form\Form(
			$this->dom,
			$this->formId,
			urlBasePage . "/workType/new/save",
			[$this, "formContent"]
		);
		$this->form->addComponent(new \iw\page\html\form\component\Text("{$this->formId}_name", N, function ($value) {
			return $this->validateInputName($value);
		}, size: 60));
		$this->form->addComponent(new \iw\page\html\form\component\Submit("{$this->formId}_submit", "zapsat"));
	}


	private function validateInputName(mixed $value): true|\iw\page\html\form\component\EntryError
	{
		return empty($value) ? new \iw\page\html\form\component\EntryError(0, "Pole nesmí být prázdné") : T;
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\dom\Exception
	 */
	public function formContent(): \iw\dom\Element
	{
		$eName= $this->form->getComponent($this->formId . "_name");
		return $this->dom->div(
			[
				\iw\html::A_CLASS => "formContent"
			],
			$this->dom->div(
				[\iw\html::A_CLASS => "formItem"],
				$this->dom->div([\iw\html::A_CLASS => "title"], "název"),
				$this->dom->div([\iw\html::A_CLASS => "input"], $eName),
				$this->componentError($eName),
				$this->dom->div([\iw\html::A_CLASS => "submit"], $this->form->getComponent($this->formId . "_submit"))
			)
		);
	}


	/**
	 * @throws \iw\dom\Exception
	 */
	private function componentError(\iw\page\html\form\component\Component $component): ?\iw\dom\Element
	{
		if(!$component->onError)
			return null;
		$e= $this->dom->div([\iw\html::A_CLASS=>"errs"]);
		foreach ($component->errorsIterator() as $error)
			$e->append($this->dom->div([\iw\html::A_CLASS=> "err"], $error->message));

		return $e;
	}



}