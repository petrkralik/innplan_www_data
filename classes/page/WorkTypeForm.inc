<?php


namespace page;


/**
 * Class WorkTypeForm
 *
 * An abstract class that forms the basis for different types of forms in the application.
 * Each subclass defines how each form component should behave.
 *
 * @package page
 *
 */
abstract class WorkTypeForm extends Page2Columns
{


	/**
	 * @var \iw\page\html\form\Form Form instance that the class holds.
	 */
	protected \iw\page\html\form\Form $form;

	/**
	 * @var int The type ID of the work.
	 */
	protected int $workTypeId;

	/**
	 * @var string The ID of the form
	 */
	protected string $formId = "workTypeForm";


	/**
	 * Abstract method to get the value of the component name.
	 *
	 * @return ?string the value of the component name
	 */
	abstract protected function getFormComponentNameValue(): ?string;


	/**
	 * Abstract method to get Form Component Seniority.
	 *
	 * @return ?int the seniority of the component
	 */
	abstract protected function getFormComponentSeniorityValue(): ?int;


	/**
	 * Abstract method to get Form Component Description.
	 *
	 * @return ?string the description of the component
	 */
	abstract protected function getFormComponentDescriptionValue(): ?string;


	/**
	 * Abstract method to save the form.
	 *
	 * @return ?bool Return whether the form has been saved or not.
	 */
	abstract public function formOnSaveFn(): ?bool;


	/**
	 * Abstract method executes after form saved success.
	 *
	 * @return ?bool Return whether the form has been saved or not.
	 */
	abstract public function formOnSaveSuccessFn(): ?bool;



	/**
	 * Function to build the form.
	 *
	 * @param   string  $url  The URL to which the form will submit.
	 *
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
	 * Function to get the content of the form component.
	 *
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
	 * Set the component error
	 *
	 * @param   \iw\page\html\form\component\Component  $component  - the component that has the error
	 *
	 * @return \iw\dom\Element|null
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
	 * Get the form component name
	 *
	 * @return \iw\page\html\form\component\Component - the component of the form's name
	 * @throws \iw\page\html\form\Exception
	 *
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
	 * Get the form component description
	 *
	 * @return \iw\page\html\form\component\Component - the description component of the form
	 * @throws \iw\page\html\form\Exception
	 *
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
	 *
	 * @throws \iw\page\html\form\Exception
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
	 * Get the form component disabled
	 *
	 * @return \iw\page\html\form\component\Component - the disabled component of the form
	 * @throws \iw\page\html\form\Exception
	 *
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


	/**
	 * Get the name of the form seniority component
	 *
	 * @return string - the name of the form seniority component
	 */
	private function getFormComponentSeniorityName(): string
	{
		return $this->formId . "_seniority";
	}


	/**
	 * Method to get the name of the form component name
	 *
	 * @return string - Returns the name of the form component, which is the formId appended with '_name'
	 */
	private function getFormComponentNameName(): string
	{
		return $this->formId."_name";
	}


	/**
	 * Method to get the description of the form component
	 *
	 * @return string - Returns the name of the description component, which is the formId appended with '_description'
	 */
	private function getFormComponentDescriptionName(): string
	{
		return $this->formId . "_description";
	}


	/**
	 * Method to get the form component disabled name
	 *
	 * @return string - Returns the name of the disabled component of the form, which is the formId appended with '_disabled'
	 */
	private function getFormComponentDisabledName(): string
	{
		return $this->formId . "_disabled";
	}


	/**
	 * Validator for the form component's name. Checks if the name is empty.
	 *
	 * @param   string  $value  - the name of the component to be validated
	 *
	 * @return true|\iw\page\html\form\component\EntryError - Returns true if the name is not empty, else returns an EntryError with an error message
	 */
	public function formComponentNameValidator(string $value): true|\iw\page\html\form\component\EntryError
	{
		return empty($value) ? new \iw\page\html\form\component\EntryError(0, "název nesmí být prázdný") : T;
	}


}