<?php


namespace page\WorkType;


/**
 * Class WorkTypeForm
 *
 * An abstract class that forms the basis for different types of forms in the application.
 * Each subclass defines how each form component should behave.
 *
 * @package page
 *
 */
abstract class WorkTypeForm extends WorkType
{


	/**
	 * @var \iw\page\html\form\Form Form instance that the class holds.
	 */
	protected \iw\page\html\form\Form $form;


	/**
	 * @var string The ID of the form
	 */
	protected string $formId = "workTypeForm";


	/**
	 * Abstract method to get the value of the component name.
	 *
	 * @return ?string the value of the component name
	 */
	abstract public function getFormComponentNameValue(\iw\page\html\form\component\Text $component): ?string;


	/**
	 * Abstract method to get Form Component Seniority.
	 *
	 * @return int|null the seniority of the component
	 */
	abstract public function getFormComponentSeniorityValue(\iw\page\html\form\component\Combobox $component): ?int;


	/**
	 * Abstract method to get Form Component Description.
	 *
	 * @return ?string the description of the component
	 */
	abstract public function getFormComponentDescriptionValue(\iw\page\html\form\component\Textarea $component): ?string;


	/**
	 * Abstract method to get the Form Component Disabled value.
	 *
	 * @param   \iw\page\html\form\component\Checkbox  $component  The component from which to get the value
	 *
	 * @return bool|null The disabled value of the component. Returns null if the value is not set.
	 */
	abstract public function getFormComponentDisabledValue(\iw\page\html\form\component\Checkbox $component): ?bool;


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
		$this->formBuildAllComponents();
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
	private function formBuildAllComponents(): void
	{
		$this->form->components->addComponents($this->getBusinessObject()->getFormComponents($this));
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
		$c= $this->getBusinessObject()->getFormComponents($this);
		$table= [
			["název", [$c->getFormComponentName(), $this->componentError($c->getFormComponentName())]],
			["popis", [$c->getFormComponentDescription(), $this->componentError($c->getFormComponentDescription())]],
			["seniorita", [$c->getFormComponentSeniority(), $this->componentError($c->getFormComponentSeniority())]],
			["uzamčeno", [$c->getFormComponentDisabled(),  $this->componentError($c->getFormComponentDisabled())]],
			[null, $this->getFormComponentSubmit()],
		];

		return [
			new \iw\page\html\arrayDecorator\ArrayDecorator($table),
			$this->form->getInnerIdComponent(),
		];
	}


	/**
	 * @throws \iw\page\html\form\Exception
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	protected function getFormComponentSubmit(): \iw\page\html\form\component\Component
	{
		$c = $this->getBusinessObject()->getFormComponents($this);
		if(!$c->componentExists($this->getFormComponentSubmitName())) {
			$c->addComponent(new \iw\page\html\form\component\Submit(
				$this->getFormComponentSubmitName(),
				"uložit"
			));
		}

		return $c->getComponent($this->getFormComponentSubmitName());
	}


	private function getFormComponentSubmitName(): string
	{
		return "buttonSubmit";
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
		if (! $component->onError)
			return null;
		$e = $this->dom->div([\iw\html::A_CLASS => "errs"]);
		foreach ($component->errorsIterator() as $error) {
			$e->append($this->dom->div([\iw\html::A_CLASS => "err"], $error->message));
		}

		return $e;
	}


}