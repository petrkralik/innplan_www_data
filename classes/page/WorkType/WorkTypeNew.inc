<?php


namespace page\WorkType;


use JetBrains\PhpStorm\NoReturn;


/**
 * Class WorkTypeNew
 * This class extends WorkTypeForm and provides functionality to create a new work type.
 *
 * @package page
 */
class WorkTypeNew extends WorkTypeForm
{


	/**
	 * ACTION_NEW is a constant to denote the 'New' action on the page
	 *
	 * @var string
	 */
	private const string ACTION_NEW = "ACTION_NEW";

	/**
	 * ACTION_SAVE is a constant to denote the 'Save' action on the page
	 *
	 * @var string
	 */
	private const string ACTION_SAVE = "ACTION_SAVE";


    /**
     * Build and setup form for the Page.
     * Depending on the detected process, form is either shown or saved.
     *
     * @return ?\iw\dom\Element Return form DOM element or show a success message when saved.
     * @throws \iw\page\html\form\Exception
	 * @throws \Random\RandomException
	 * @throws \iw\Exception
     */
    function getContentMain(): ?\iw\dom\Element
    {
        $this->buildForm(\urlBasePage. "/workType/new/save");
        $showForm = true;
        if ($this->detectProcess() == self::ACTION_SAVE) {
            if ($this->form->isSaved()) {
				$showForm = false;
			} else {
				$showForm = ! $this->form->save();
			}
        }
        return $this->dom->div(
            [
                \iw\html::A_CLASS => "workTypeNew",
            ],
            $this->dom->h1(\N, "nový typ práce"),
            $showForm ? $this->form : \N);
    }


    /**
     * Detects the action based on uriMatches[1].
     *
     * @return string Returns detected action
     */
    function detectProcess(): string
    {
        return match ($this->uriMatches[1]) {
            "new" => self::ACTION_NEW,
            "save" => self::ACTION_SAVE
        };
    }


	/**
	 * Saves the form. Operation is stubbed out in this method.
	 *
	 * @return bool Always false as a save operation is not implemented.
	 * @throws \iw\page\html\form\Exception
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
    public function formOnSaveFn(): bool
    {
        $obj = new \businessObject\WorkType();
		$c= $obj->getFormComponents($this);
		$data = [
            \entity\WorkType::ATTRIBUTE_NAME => $c->getFormComponentName()->getValue(),
			\entity\WorkType::ATTRIBUTE_DESCRIPTION => $c->getFormComponentDescription()->getValue(),
            \entity\WorkType::ATTRIBUTE_SENIORITY_ID => $c->getFormComponentSeniority()->getValue(),
			\entity\WorkType::ATTRIBUTE_DISABLED => $c->getFormComponentDisabled()->isCheckedInForm()? true: null,
        ];
		var_dump($data);
		try {
			return $obj->create($data);
		}
		catch (\iw\api\Exception $ex) {
			var_dump($ex);
		}

		return false;
    }


    #[NoReturn]
    public function formOnSaveSuccessFn(): ?bool
    {
        $this->dom->redirect(\urlBasePage. "/workType/list");
    }


	/**
	 * This method retrieves the name component of the form
	 *
	 * @param   \iw\page\html\form\component\Text  $component
	 *
	 * @return ?string Returns null as no name is provided
	 */
	public function getFormComponentNameValue(\iw\page\html\form\component\Text $component): ?string
	{
		return $this->request->getProperty($component->name);
	}


	/**
	 * This method retrieves the seniority id value
	 *
	 * @param   \iw\page\html\form\component\Combobox  $component  *
	 *
	 * @return int|null Returns null as no value is given
	 */
	public function getFormComponentSeniorityValue(\iw\page\html\form\component\Combobox $component): ?int
	{
		return (int) $this->request->getProperty($component->name);
	}


	/**
	 * This method retrieves the description of the work type.
	 *
	 * @param   \iw\page\html\form\component\Textarea  $component  *
	 *
	 * @return ?string Returns null as no description is provided.
	 */
	public function getFormComponentDescriptionValue(\iw\page\html\form\component\Textarea $component): ?string
	{
		return $this->request->getProperty($component->name);
	}


	public function getFormComponentDisabledValue(\iw\page\html\form\component\Checkbox $component): ?bool
	{
		return $this->request->getProperty($component->name)? true: null;
	}


}