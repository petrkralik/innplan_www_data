<?php


namespace page\WorkType;


use JetBrains\PhpStorm\NoReturn;


class WorkTypeEdit extends \page\WorkType\WorkTypeForm
{


	const string ACTION_SAVE = "save";
	const string ACTION_EDIT = "edit";


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 * @throws \Random\RandomException
	 * @throws \iw\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		try {
			$this->getBusinessObject();
			$this->buildForm(\urlBasePage. "/workType/{$this->getWorkTypeId()}/edit/save");
		}
		catch (\businessObject\Exception $ex) {
			if($ex->error== \businessObject\Error::NO_OBJECT_LIKE_THIS)
				$content= $this->domErrorNonexistentObject();
			elseif($ex->error== \businessObject\Error::API_DATA_LOAD)
				$content= $this->donErrorObjectLoading();
		}
		if($this->detectProcess()== self::ACTION_SAVE) {
			if($this->form->isSaved()) {
				$content= $this->domFormResave();
			} else {
				if($this->form->save())
					$content= $this->domFormSaved();
				else
					$content= $this->form;
			}
		} else {
			$content= $this->form;
		}

		return $this->dom->div(
			[
				\iw\html::A_CLASS => "workTypeEdit",
			],
			$this->dom->h1(\N, "úprava typu práce"),
			$content
		);
	}


	private function domFormSaved(): \iw\dom\Element
	{
		return $this->dom->p(\N, "Uloženo.");
	}


	private function domFormResave(): \iw\dom\Element
	{
		return $this->dom->p(\N, "Program zabránil opětovnému uložení.");
	}


	private function domErrorNonexistentObject(): \iw\dom\Element
	{
		return $this->dom->p(\N, "Takový objekt neexistuje.");
	}


	private function donErrorObjectLoading(): \iw\dom\Element
	{
		return $this->dom->p(\N, "Problém s načtením objektu");
	}


	private function detectProcess(): string
	{
		return match ($this->uriMatches[2] ?? null) {
			"save" => self::ACTION_SAVE,
			default => self::ACTION_EDIT
		};
	}


	/**
	 * @param   \iw\page\html\form\component\Text  $component
	 *
	 * @return string|null
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	public function getFormComponentNameValue(\iw\page\html\form\component\Text $component): ?string
	{
		return $this->getFormValueStd($component);
	}


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	public function getFormComponentDescriptionValue(\iw\page\html\form\component\Textarea $component): ?string
	{
		return $this->getFormValueStd($component);
	}


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	public function getFormComponentSeniorityValue(\iw\page\html\form\component\Combobox $component): ?int
	{
		return $this->getFormValueStd($component);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	public function getFormComponentDisabledValue(\iw\page\html\form\component\Checkbox $component): ?bool
	{
		return $this->getFormValueStd($component);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function getFormValueStd(\iw\page\html\form\component\ComponentWithValue $component): mixed
	{
		return $this->request->isPropertySet($component->name)
			? $this->request->getProperty($component->name)
			: $this->getBusinessObject()->{$component->programPropertyName}->getValue();
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	public function formOnSaveFn(): ?bool
	{
		$w= $this->getBusinessObject();
		$c= $w->getFormComponents($this);
		echo "Components count: ". $c->componentsCount(). LF;
		$w->name->setValue($c->getFormComponentName()->getValue());
		$w->description->setValue($c->getFormComponentDescription()->getValue());
		$w->workTypeSeniorityId->setValue($c->getFormComponentSeniority()->getValue());
		$w->disabled->setValue($c->getFormComponentDisabled()->isCheckedInForm()? true: null);

		return $w->saveChanges();
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	#[NoReturn] public function formOnSaveSuccessFn(): ?bool
	{
		$this->dom->redirect($this->getBusinessObject()->urlPageDetail());
	}


}