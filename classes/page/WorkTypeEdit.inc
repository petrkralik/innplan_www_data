<?php


namespace page;


class WorkTypeEdit extends Page2Columns
{

	private \businessObject\WorkType $workType;
	private \iw\page\html\form\Form $form;
	private string $formId= "workTypeFormEdit";
	private int $workTypeId;


	/**
	 * @throws \businessObject\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$this->loadObject();
		$this->buildForm();
		$showForm = true;

		return $this->dom->div(
			[
				\iw\html::A_CLASS => "workTypeNew"
			],
			$this->dom->h1(N, "úprava typu práce"),
			$showForm ? $this->form : N
		);
	}

	private function buildForm(): void
	{
		$this->form= new \iw\page\html\form\Form(
			$this->dom,
			$this->formId,
			urlBasePage. "/workType/{$this->getWorkTypeId()}/edit/save",
			[$this, "formOnGetContent"],
			[$this, "formOnSave"],
			null,
			null,
			null,
			[$this, "formOnSaveSuccess"],
			null
		);
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function getFormComponentName(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentNameName()))
			$this->form->components->addComponent(new \iw\page\html\form\component\Text(
					$this->getFormComponentNameName(),
					validator: [$this, "formComponentNameValidator"],
					value: $this->workType->name->getValue(),
					size: 50
				));

		return $this->form->components->getComponent($this->getFormComponentNameName());
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function getFormComponentDescription(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentDescriptionName()))
			$this->form->components->addComponent(new \iw\page\html\form\component\Textarea(
					$this->getFormComponentDescriptionName(),
					value: $this->workType->description->getValue(),
					cols: 47,
					rows: 8
				));

		return $this->form->components->getComponent($this->getFormComponentDescriptionName());
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function getFormComponentSeniority(): \iw\page\html\form\component\Component
	{
		if(!$this->form->components->componentExists($this->getFormComponentSeniorityName())) {
			$this->form->components->addComponent(new \iw\page\html\form\component\Combobox(
				$this->getFormComponentSeniorityName(),
				selectedValue: $this->workType->workTypeSeniorityId->getValue(),
				optionSet: new \iw\page\html\form\component\OptionSet(
					new \iw\page\html\form\component\Option("", ""),
					new \iw\page\html\form\component\Option("1", "Junior"),
					new \iw\page\html\form\component\Option("2", "Medior"),
					new \iw\page\html\form\component\Option("3", "Senior"),
				)
			));
		}

		return $this->form->components->getComponent($this->getFormComponentSeniorityName());
	}


	public function formComponentNameValidator(string $value): true|\iw\page\html\form\component\EntryError
	{
		return empty($value) ? new \iw\page\html\form\component\EntryError(0, "název nesmí být prázdný") : T;
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


	private function getWorkTypeId(): int
	{
		return $this->workTypeId= (int)$this->uriMatches[1];
	}


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\dom\Exception
	 * @throws \Random\RandomException
	 * @throws \iw\page\html\form\component\Exception
	 */
	public function formOnGetContent(): mixed
	{
		$table= [
			["název", [$this->getFormComponentName(), $this->componentError($this->getFormComponentName())]],
			["popis", [$this->getFormComponentDescription(), $this->componentError($this->getFormComponentDescription())]],
			["seniorita"], [$this->getFormComponentSeniority(), $this->componentError($this->getFormComponentSeniority())],
		];

		return [
			new \iw\page\html\arrayDecorator\ArrayDecorator($this->dom, $table),
			$this->form->getInnerIdComponent()
		];
	}


	public function formOnSave(): mixed
	{
		return null;
	}


	public function formOnSaveSuccess(): void
	{
		// code here
	}

	/**
	 * @throws \businessObject\Exception
	 */
	private function loadObject(): void
	{
		$this->workType = new \businessObject\WorkType($this->getWorkTypeId());
    	$this->workType->loadData();
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


}