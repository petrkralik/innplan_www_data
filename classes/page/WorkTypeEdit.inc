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
		}
		catch (\businessObject\Exception $ex) {
			echo $ex->error->value;
		}
		$this->buildForm(urlBasePage. "/workType/{$this->getWorkTypeId()}/edit/save");

		$showForm = true;

		return $this->dom->div(
			[
				\iw\html::A_CLASS => "workTypeNew",
			],
			$this->dom->h1(N, "úprava typu práce"),
			$showForm ? $this->form : N
		);
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


	public function formOnSaveFn(): ?bool
	{
		return null;
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