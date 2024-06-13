<?php


namespace businessObject;


class WorkTypeFormComponents extends FormComponents
{


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
	public function buildFormComponents(): void
	{
		$this->getFormComponentName();
		$this->getFormComponentDescription();
		$this->getFormComponentSeniority();
		$this->getFormComponentDisabled();
	}


	/**
	 * @return \iw\page\html\form\component\Text
	 * @throws \iw\page\html\form\Exception
	 */
	public function getFormComponentName(): \iw\page\html\form\component\Text
	{
		$id= $this->getFormComponentNameId();
		if(!$this->componentExists($this->getFormComponentNameId())) {
			$c= new \iw\page\html\form\component\Text(
				$id,
				programPropertyName: \entity\WorkType::ATTRIBUTE_NAME,
				validator: [$this, "formComponentNameValidator"],
				size: 50
			);
			$c->setValue($this->controlObject->getFormComponentNameValue($c));
			$this->addComponent($c);
		}


		return $this->getComponent($id);
	}


	public function getFormComponentNameId(): string
	{
		return \entity\WorkType::ATTRIBUTE_NAME;
	}


	/**
	 * Get the form component description
	 *
	 * @return \iw\page\html\form\component\Textarea - the description component of the form
	 * @throws \iw\page\html\form\Exception
	 */
	public function getFormComponentDescription(): \iw\page\html\form\component\Textarea
	{
		if(!$this->componentExists($this->getFormComponentDescriptionId())) {
			$c = new \iw\page\html\form\component\Textarea(
				$this->getFormComponentDescriptionId(),
				programPropertyName: \entity\WorkType::ATTRIBUTE_DESCRIPTION,
				cols: 47,
				rows: 8);
			$c->setValue($this->controlObject->getFormComponentDescriptionValue($c));
			$this->addComponent($c);
		}

		return $this->getComponent($this->getFormComponentDescriptionId());
	}


	public function getFormComponentDescriptionId(): string
	{
		return \entity\WorkType::ATTRIBUTE_DESCRIPTION;
	}


	/**
	 * @return \iw\page\html\form\component\Combobox
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
	public function getFormComponentSeniority(): \iw\page\html\form\component\Combobox
	{
		if(!$this->componentExists($this->getFormComponentSeniorityId())) {
			$c= new \iw\page\html\form\component\Combobox(
				$this->getFormComponentSeniorityId(),
				programPropertyName: \entity\WorkType::ATTRIBUTE_SENIORITY_ID,
				validator: [$this, "formComponentSeniorityValidator"],
				optionSet: $optionSet= new \iw\page\html\form\component\OptionSet(
					false,
					new \iw\page\html\form\component\Option("0", ""),
					new \iw\page\html\form\component\Option("1", "Junior"),
					new \iw\page\html\form\component\Option("2", "Medior"),
					new \iw\page\html\form\component\Option("3", "Senior"),
				)
			);

			$this->addComponent($c);
			$optionSet->selectOptionByValue($this->controlObject->getFormComponentSeniorityValue($c));
		}

		return $this->getComponent($this->getFormComponentSeniorityId());
	}


	public function getFormComponentSeniorityId(): string
	{
		return \entity\WorkType::ATTRIBUTE_SENIORITY_ID;
	}


	/**
	 * Get the form component disabled
	 *
	 * @return \iw\page\html\form\component\Checkbox - the disabled component of the form
	 * @throws \iw\page\html\form\Exception
	 */
	public function getFormComponentDisabled(): \iw\page\html\form\component\Checkbox
	{
		if(!$this->componentExists($this->getFormComponentDisabledId())) {
			$c= new \iw\page\html\form\component\Checkbox(
					$this->getFormComponentDisabledId(),
					null,
					\entity\WorkType::ATTRIBUTE_DISABLED,
					[$this, "formComponentDisabledValidator"],
					"1",
					null,
					null,
					null
				);
			$c->checked= $this->controlObject->getFormComponentDisabledValue($c);
			$this->addComponent($c);
		}

		return $this->getComponent($this->getFormComponentDisabledId());
	}


	public function getFormComponentDisabledId(): string
	{
		return \entity\WorkType::ATTRIBUTE_DISABLED;
	}


	/**
	 * Validator for the form component's name. Checks if the name is empty.
	 *
	 * @param \iw\page\html\form\component\ComponentWithValue $component
	 *
	 * @return bool - Returns true if the name is not empty, else returns an EntryError with an error message
	 */
	public function formComponentNameValidator(\iw\page\html\form\component\ComponentWithValue $component): bool
	{
		$value= $component->getValue();
		if(empty($value)) {
			$component->addError(new \iw\page\html\form\component\EntryError(0, "název nesmí být prázdný"));
			return false;
		}

		return true;
	}


	public function formComponentSeniorityValidator(\iw\page\html\form\component\ComponentWithValue $component): bool
	{
		$value= $component->getValue();
		if (! is_numeric($value) || intval($value) <= 0) {
			$component->addError(new \iw\page\html\form\component\EntryError(0, "seniorita musí být vyplněna"));
			return false;
		} else {
			$component->setValue((int) $component->getValue());
		}

		return true;
	}


	public function formComponentDisabledValidator(\iw\page\html\form\component\ComponentWithValue $component): bool
	{
		return true;
	}



}