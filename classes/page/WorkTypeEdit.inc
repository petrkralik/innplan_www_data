<?php


namespace page;


class WorkTypeEdit extends WorkTypeForm
{


	const string ACTION_SAVE = "save";
	const string ACTION_EDIT = "edit";


	private \businessObject\WorkType $workType;


	/**
	 * @throws \businessObject\Exception
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		try {
			$this->loadObject();
			$this->buildForm(urlBasePage. "/workType/{$this->getWorkTypeId()}/edit/save");
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
			$this->dom->h1(N, "úprava typu práce"),
			$content
		);
	}


	private function domFormSaved(): \iw\dom\Element
	{
		return $this->dom->p(N, "Uloženo.");
	}


	private function domFormResave(): \iw\dom\Element
	{
		return $this->dom->p(N, "Program zabránil opětovnému uložení.");
	}


	private function domErrorNonexistentObject(): \iw\dom\Element
	{
		return $this->dom->p(N, "Takový objekt neexistuje.");
	}


	private function donErrorObjectLoading(): \iw\dom\Element
	{
		return $this->dom->p(N, "Problém s načtením objektu");
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
	 */
	protected function getFormComponentNameValue(): ?string
	{
		return $this->workType->name->getValue();
	}


	/**
	 * @throws \businessObject\property\Exception
	 */
	protected function getFormComponentDescriptionValue(): ?string
	{
		return $this->workType->description->getValue();
	}


	/**
	 * @throws \businessObject\property\Exception
	 */
	protected function getFormComponentSeniorityValue(): ?int
	{
		return $this->workType->workTypeSeniorityId->getValue();
	}


	/**
	 * @throws \businessObject\property\Exception
	 */
	protected function getFormComponentDisabledValue(): ?bool
	{
		return $this->workType->disabled->getValue();
	}


	private function getWorkTypeId(): int
	{
		return $this->workTypeId= (int)$this->uriMatches[1];
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
	public function formOnSaveFn(): ?bool
	{
		$data = [
			\entity\WorkType::ATTRIBUTE_NAME => $this->getFormComponentName()->value,
			\entity\WorkType::ATTRIBUTE_DESCRIPTION => $this->getFormComponentDescription()->value,
			\entity\WorkType::ATTRIBUTE_SENIORITY_ID => $this->getFormComponentSeniority()->value,
			\entity\WorkType::ATTRIBUTE_DISABLED => $this->getFormComponentDisabled()->value,
		];

		var_dump($data);

		return false;
	}


	public function formOnSaveSuccessFn(): ?bool
	{
		return null;
	}


	/**
	 * @throws \businessObject\Exception
	 */
	private function loadObject(): void
	{
		$this->workType = new \businessObject\WorkType($this->getWorkTypeId());
    	$this->workType->loadData();
	}


}