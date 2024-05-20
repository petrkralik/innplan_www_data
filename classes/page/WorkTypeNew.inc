<?php


namespace page;


use JetBrains\PhpStorm\NoReturn;


class WorkTypeNew extends Page2Columns
{


    /**
     * Identifier for the 'New' action in the page
     * @var string
     */
    private const string ACTION_NEW = "ACTION_NEW";

    /**
     * Identifier for the 'Save' action in the page
     * @var string
     */
    private const string ACTION_SAVE = "ACTION_SAVE";

    /**
     * Form object used for handling form operations
     * @var \iw\page\html\form\Form
     */
    private \iw\page\html\form\Form $form;

    /**
     * Identifier for the form
     * @var string
     */
    private string $formId = "workTypeNewForm";


    /**
     * Build and setup form for the Page.
     * Depending on the detected process, form is either shown or saved.
     *
     * @return ?\iw\dom\Element Return form DOM element or show a success message when saved.
     * @throws \iw\page\html\form\Exception
     */
    function getContentMain(): ?\iw\dom\Element
    {
        $this->buildForm();
        $showForm = true;
        if ($this->detectProcess() == self::ACTION_SAVE) {
            if ($this->form->isSaved())
                $showForm = false;
            else
                $showForm = !$this->form->save();
        }

        return $this->dom->div(
            [
                \iw\html::A_CLASS => "workTypeNew"
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
     * Constructs the form object and adds components to the form.
     *
     * @throws \iw\page\html\form\Exception Exception thrown in form methods
     */
    private function buildForm(): void
    {
        $this->form = new \iw\page\html\form\Form(
            $this->dom,
            $this->formId,
            urlBasePage . "/workType/new/save",
            [$this, "formOnGetContent"],
            [$this, "formOnSave"],
            N,
            N,
            N,
            [$this, "onSaveSuccess"],
            N
        );
        $this->form->components->addComponent($this->formNewComponentName());
		$this->form->components->addComponent($this->formNewComponentDescription());
        $this->form->components->addComponent(new \iw\page\html\form\component\Submit("{$this->formId}_submit", "zapsat"));
		echo $this->form->components->componentsCount(). LF;
    }


    /**
     *
     * /**
     * This method is responsible for generating the content of the form. It first fetches the form component associated
     * with the name using the form's getComponent method. It then creates a new 'div' DOM element to encapsulate the form content,
     * with a 'formItem' and related classes for each part of the form such as the title, input, and submit sections.
     *
     * Inside each of these sections, further 'div' DOM elements are created and appropriate classes alongside respective
     * content are attached. For instance, the 'input' section receives the form component itself and any associated errors
     * as its content.
     *
     * @return \iw\dom\Element A Dom element encapsulating the entire form content along with its associated errors and submit button.
     *
     * @throws \iw\page\html\form\Exception if there is an error fetching a component from the form.
     * @throws \iw\dom\Exception If there is an error with DOM manipulation
     * @throws \Random\RandomException
     */
    public function formOnGetContent(): \iw\dom\Element
    {
        $eName = $this->form->components->getComponent($this->formId . "_name");

        return $this->dom->div(
            [
                \iw\html::A_CLASS => "formContent"
            ],
            $this->dom->div(
                [\iw\html::A_CLASS => "formItem"],
                $this->dom->div([\iw\html::A_CLASS => "title"], "název"),
                $this->dom->div([\iw\html::A_CLASS => "input"], $eName, $this->componentError($eName)),
                $this->form->getInnerIdComponent(),
                $this->dom->div([\iw\html::A_CLASS => "submit"], $this->form->components->getComponent($this->formId . "_submit"))
            )
        );
    }


    /**
     * Returns a new instance of Text component for the form.
     *
     * @return \iw\page\html\form\component\Text Returns Text component.
     */
    private function formNewComponentName(): \iw\page\html\form\component\Text
    {
        return new \iw\page\html\form\component\Text(
            "{$this->formId}_name",
            validator: function ($value) {
                return $this->validateInputName($value);
            },
            size: 50
        );
    }


    /**
     * Returns a new instance of Text component for the form.
     *
     * @return \iw\page\html\form\component\Textarea Returns Text component.
     */
    private function formNewComponentDescription(): \iw\page\html\form\component\Textarea
    {
        return new \iw\page\html\form\component\Textarea(
            "{$this->formId}_description"
        );
    }



    /**
     * Saves the form. Operation is stubbed out in this method.
     *
     * @return bool Always false as a save operation is not implemented.
     * @throws \iw\api\Exception
     * @throws \iw\page\html\form\Exception
     * @throws \businessObject\Exception
     * @throws \businessObject\property\Exception
     */
    public function formOnSave(): bool
    {
        $data = [
            \entity\WorkType::ATTRIBUTE_NAME => $this->form->components->getComponent($this->formId . "_name")->value,
            \entity\WorkType::ATTRIBUTE_SENIORITY_ID => 1,
        ];
        $obj = new \businessObject\WorkType();

        return $obj->create($data);
    }


    /**
     * Handles successful form submission.
     * On success, this method redirects the user to the base work type page.
     *
     * @return void
     * @throws \iw\dom\Exception if there is an error redirecting
     *
     */
    #[NoReturn]
    public function onSaveSuccess(): void
    {
        $this->dom->redirect(urlBasePage . "/workType/list");
    }


   /**
     * Validates if input is empty or not. If empty an error is thrown.
     *
     * @param mixed $value Value to be validated.
     *
     * @return true|\iw\page\html\form\component\EntryError
     */
    private function validateInputName(mixed $value): true|\iw\page\html\form\component\EntryError
    {
        return empty($value) ? new \iw\page\html\form\component\EntryError(0, "Pole nesmí být prázdné") : T;
    }


    /**
     * This is a private helper function that is responsible for handling form component errors.
     * It takes an instance of the Component class as argument and checks if any error has occurred using the onError property of the component.
     *
     * If there is no error, it returns null. Otherwise, it creates a new 'div' DOM element with the class 'errs'.
     * It then loops over each error in the component's error iterator and appends a new 'div' DOM element to 'errs' div,
     * with an 'err' class and the error message as content.
     *
     * @param \iw\page\html\form\component\Component $component The form component to check for errors
     *
     * @return ?\iw\dom\Element A DOM element containing error messages or null if there are no errors
     *
     * @throws \iw\dom\Exception If there is an error with DOM manipulation
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


}