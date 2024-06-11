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
		try {
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
		}
		catch (\iw\Exception $ex) {
			throw $ex;
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
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	public function getFormComponentNameValue(): ?string
	{
		$id= $this->getBusinessObject()->getFormComponents($this)->getFormComponentNameId();
		return $this->request->isPropertySet($id)
			? $this->request->getProperty($id)
			: $this->getBusinessObject()->name->getValue();
	}


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	protected function getFormComponentDescriptionValue(): ?string
	{
		$id= $this->getBusinessObject()->getFormComponents($this)->getFormComponentDescriptionId();
		return $this->request->isPropertySet($id)
			? $this->request->getProperty($id)
			: $this->getBusinessObject()->description->getValue();
	}


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	protected function getFormComponentSeniorityValue(): ?int
	{
		$id= $this->getBusinessObject()->getFormComponents($this)->getFormComponentSeniorityId();
		return $this->request->isPropertySet($id)
			? $this->request->getProperty($id)
			: $this->getBusinessObject()->workTypeSeniorityId->getValue();
	}


	/**
	 * @throws \businessObject\property\Exception
	 * @throws \businessObject\Exception
	 */
	protected function getFormComponentDisabledValue(): ?bool
	{
		$id= $this->getBusinessObject()->getFormComponents($this)->getFormComponentDisabledId();
		return $this->request->isPropertySet($id)
			? $this->request->getProperty($id)
			: $this->getBusinessObject()->disabled->getValue();
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