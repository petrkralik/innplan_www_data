<?php


namespace page;


abstract class WorkTypeForm extends Page2Columns
{


	protected \iw\page\html\form\Form $form;
	protected int $workTypeId;
	protected string $formId= "workTypeForm";


	abstract protected function getFormComponentNameValue(): ?string;
	abstract protected function getFormComponentSeniorityValue(): ?int;
	abstract protected function getFormComponentDescriptionValue(): ?string;
	abstract public function formOnSaveFn(): ?bool;
	abstract public function formOnSaveSuccessFn(): ?bool;



	/**
	 * @throws \iw\Exception
	 * @throws \Random\RandomException
	 */
	protected function buildForm(string $url): void
	{
		$this->form= new \iw\page\html\form\Form(
			$this->formId,
			$url,
			[$this, "formOnGetContentFn"],
			[$this, "formOnSaveFn"],
			null,
			null,
			null,
			[$this, "formOnSaveSuccessFn"],
			null
		);
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\dom\Exception
	 * @throws \Random\RandomException
	 * @throws \iw\page\html\form\component\Exception
	 */
	public function formOnGetContentFn(): array
	{
		$table= [
			["název", [$this->getFormComponentName(), $this->componentError($this->getFormComponentName())]],
			["popis", [$this->getFormComponentDescription(), $this->componentError($this->getFormComponentDescription())]],
			["seniorita", [$this->getFormComponentSeniority(), $this->componentError($this->getFormComponentSeniority())]],
			["uzamčeno", [$this->getFormComponentDisabled(),  $this->componentError($this->getFormComponentDisabled())]],
		];

		return [
			new \iw\page\html\arrayDecorator\ArrayDecorator($table),
			$this->form->getInnerIdComponent(),
		];
	}


	/**
	 * @throws \iw\dom\Exception
	 */
	private function componentError(\iw\page\html\form\component\Component $component): ?\iw\dom\Element
	{
		if (!$component->onError)
			return null;
		$e = $this->dom->div([\iw\html::A_CLASS => "errs"]);
		foreach ($component->errorsIterator() as $error)
			$e->append($this->dom->div([\iw\html::A_CLASS => "err"], $error->message));

		return $e;
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	private function getFormComponentName(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentNameName()))
			$this->form->components->addComponent(new \iw\page\html\form\component\Text(
				$this->getFormComponentNameName(),
				validator: [$this, "formComponentNameValidator"],
				value: $this->getFormComponentNameValue(),
				size: 50
			));

		return $this->form->components->getComponent($this->getFormComponentNameName());
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	private function getFormComponentDescription(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentDescriptionName()))
			$this->form->components->addComponent(new \iw\page\html\form\component\Textarea(
				$this->getFormComponentDescriptionName(),
				value: $this->getFormComponentDescriptionValue(),
				cols: 47,
				rows: 8
			));

		return $this->form->components->getComponent($this->getFormComponentDescriptionName());
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
	private function getFormComponentSeniority(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentSeniorityName())) {
			$this->form->components->addComponent(new \iw\page\html\form\component\Combobox(
				$this->getFormComponentSeniorityName(),
				optionSet: $optionSet= new \iw\page\html\form\component\OptionSet(
					false,
					new \iw\page\html\form\component\Option("", ""),
					new \iw\page\html\form\component\Option("1", "Junior"),
					new \iw\page\html\form\component\Option("2", "Medior"),
					new \iw\page\html\form\component\Option("3", "Senior"),
				)
			));
			$optionSet->selectOptionByValue($this->getFormComponentSeniorityValue());
		}

		return $this->form->components->getComponent($this->getFormComponentSeniorityName());
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	protected function getFormComponentDisabled(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentDisabledName())) {
			$this->form->components->addComponent(new \iw\page\html\form\component\Checkbox(
				$this->getFormComponentDisabledName()
			));
		}

		return $this->form->components->getComponent($this->getFormComponentDisabledName());
	}


	private function getFormComponentSeniorityName(): string
	{
		return $this->formId . "_seniority";
	}


	private function getFormComponentNameName(): string
	{
		return $this->formId. "_name";
	}


	private function getFormComponentDescriptionName(): string
	{
		return $this->formId . "_description";
	}


	private function getFormComponentDisabledName(): string
	{
		return $this->formId . "_disabled";
	}


	public function formComponentNameValidator(string $value): true|\iw\page\html\form\component\EntryError
	{
		return empty($value) ? new \iw\page\html\form\component\EntryError(0, "název nesmí být prázdný") : T;
	}


}