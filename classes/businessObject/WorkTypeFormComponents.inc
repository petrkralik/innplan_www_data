<?php


namespace businessObject;


class WorkTypeFormComponents extends FormComponents
{



	public function __construct(\page\Page $controlObject)
	{
		parent::__construct($controlObject);
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 */
	public function buildFormComponents(): void
	{
		$this->getFormComponentName();
	}


	/**
	 * @return \iw\page\html\form\component\Text
	 * @throws \iw\page\html\form\Exception
	 */
	private function getFormComponentName(): \iw\page\html\form\component\Text
	{
		var_dump($this->controlObject);
		if(!$this->componentExists($this->getFormComponentNameId()))
			$this->addComponent(
				new \iw\page\html\form\component\Text(
					$this->getFormComponentNameId(),
					programPropertyName: \entity\WorkType::ATTRIBUTE_NAME,
					validator: [$this, "formComponentNameValidator"],
					value: $this->controlObject->getFormComponentNameValue(),
					size: 50
				)
			);

		return $this->getComponent($this->getFormComponentNameId());
	}


	private function getFormComponentNameId(): string
	{
		return \entity\WorkType::ATTRIBUTE_NAME;
	}


	/**
	 * Get the form component description
	 *
	 * @return \iw\page\html\form\component\Textarea - the description component of the form
	 * @throws \iw\page\html\form\Exception
	 */
	private function getFormComponentDescription(): \iw\page\html\form\component\Textarea
	{
		if(!$this->componentExists($this->getFormComponentDescriptionId()))
			$this->addComponent(
				new \iw\page\html\form\component\Textarea(
					$this->getFormComponentDescriptionId(),
					programPropertyName: \entity\WorkType::ATTRIBUTE_DESCRIPTION,
					value: $this->controlObject->getFormComponentDescriptionValue(),
					cols: 47,
					rows: 8
				)
			);

		return $this->getComponent($this->getFormComponentDescriptionId());
	}


	private function getFormComponentDescriptionId(): string
	{
		return \entity\WorkType::ATTRIBUTE_DESCRIPTION;
	}


	/**
	 * @return \iw\page\html\form\component\Combobox
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 * @throws \iw\page\html\form\Exception
	 */
	protected function getFormComponentSeniority(): \iw\page\html\form\component\Combobox
	{
		if(!$this->componentExists($this->getFormComponentSeniorityId())) {
			$this->addComponent(
				new \iw\page\html\form\component\Combobox(
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
				)
			);
			$optionSet->selectOptionByValue($this->controlObject->getFormComponentSeniorityValue());
		}

		return $this->getComponent($this->getFormComponentSeniorityId());
	}


	private function getFormComponentSeniorityId(): string
	{
		return \entity\WorkType::ATTRIBUTE_SENIORITY_ID;
	}


	/**
	 * Get the form component disabled
	 *
	 * @return \iw\page\html\form\component\Checkbox - the disabled component of the form
	 * @throws \iw\page\html\form\Exception
	 */
	protected function getFormComponentDisabled(): \iw\page\html\form\component\Checkbox
	{
		if(!$this->componentExists($this->getFormComponentDisabledId())) {
			$this->addComponent(
				new \iw\page\html\form\component\Checkbox(
					$this->getFormComponentDisabledId(),
					null,
					\entity\WorkType::ATTRIBUTE_DISABLED,
					[$this, "formComponentDisabledValidator"],
					"1",
					null,
					$this->controlObject->getFormComponentDisabledValue(),
					null
				)
			);
		}

		return $this->getComponent($this->getFormComponentDisabledId());
	}


	private function getFormComponentDisabledId(): string
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