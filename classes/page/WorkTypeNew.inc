<?php


namespace page;


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
     */
    function getContentMain(): ?\iw\dom\Element
    {
        $this->buildForm(urlBasePage. "/workType/new/save");
        $showForm = true;
        if ($this->detectProcess() == self::ACTION_SAVE) {
            if ($this->form->isSaved())
                $showForm = false;
            else
                $showForm = !$this->form->save();
        }

        return $this->dom->div(
            [
                \iw\html::A_CLASS => "workTypeNew",
            ],
            $this->dom->h1(N, "nový typ práce"),
            $showForm ? $this->form : N
        );
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
	 * @throws \iw\api\Exception
	 * @throws \iw\page\html\form\Exception
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 * @throws \iw\page\html\form\component\Exception
	 */
    public function formOnSaveFn(): bool
    {
        $data = [
            \entity\WorkType::ATTRIBUTE_NAME => $this->getFormComponentName()->value,
			\entity\WorkType::ATTRIBUTE_DESCRIPTION => $this->getFormComponentDescription()->value,
            \entity\WorkType::ATTRIBUTE_SENIORITY_ID => $this->getFormComponentSeniority()->value,
			\entity\WorkType::ATTRIBUTE_DISABLED => $this->getFormComponentDisabled()->value,
        ];

		echo json_encode($data);
		die();

        $obj = new \businessObject\WorkType();

        return $obj->create($data);
    }


    #[NoReturn]
    public function formOnSaveSuccessFn(): ?bool
    {
        $this->dom->redirect(urlBasePage . "/workType/list");
    }


	/**
	 * This method retrieves the name component of the form
	 *
	 * @return ?string Returns null as no name is provided
	 */
	protected function getFormComponentNameValue(): ?string
	{
		return $this->request->{$this->getFormComponentNameId()};
	}


	/**
	 * This method retrieves the seniority id value
	 *
	 * @return ?int Returns null as no value is given
	 */
	protected function getFormComponentSeniorityValue(): ?int
	{
		return $this->request->{$this->getFormComponentSeniorityId()};
	}


	/**
	 * This method retrieves the description of the work type.
	 *
	 * @return ?string Returns null as no description is provided.
	 */
	protected function getFormComponentDescriptionValue(): ?string
	{
		return $this->request->{$this->getFormComponentDescriptionId()};
	}


	protected function getFormComponentDisabledValue(): ?bool
	{
		return $this->request->{$this->getFormComponentDisabledId()}? true: null;
	}


}