<?php


namespace page;


class WorkTypeNew extends Page2Columns
{


	private \iw\page\html\form\Form $form;


	function getContentMain(): ?\iw\dom\Element
	{
		//$this->form();
		return $this->dom->div(
			[
				\iw\html::A_CLASS=> "workTypeNew"
			],
			$this->dom->h1(N, "nový typ práce"),
			$this->form()
		);
	}


	private function form()
	{
		$formId= "workTypeNewForm";
		$this->form= new \iw\page\html\form\Form($this->dom, $formId);
		$feName= new \iw\page\html\form\component\Input("{$formId}_name");
		$feName->size= 60;
		$this->form->addComponent($feName);

		return $this->dom->div(
			N,
			$feName
		);


//		$this->form->addComponent(new \iw\html\page\form\component\Text("Název:", "name"));
//        	$this->form->addComponent(new \iw\html\page\form\component\Textarea("Popis:", "description", 5, 50));
//        	$this->form->addComponent(new \iw\html\page\form\component\File("Obrázek:", "image"));
//		return $this->dom->form([
//    			\iw\html::ACTION  => \iw\html::ACTION_SELF,
//    			\iw\html::METHOD  => \iw\html::METHOD_POST,
//    			\iw\html::ENCTYPE => \iw\html::ENCTYPE_MULTIPART_FORM_DATA,
//    		], $this->dom->fieldset($this->dom->legend("Nový typ práce"), $this->dom->label("Název:"), $this->dom->input(\iw\html::TYPE_TEXT, "name"),
//    		$this->dom->br(), $this->dom->label("Popis:"), $this->dom->textarea("description", 5, 50), $this->dom->br(), $this->dom->label("Obrázek:"),
//    		$this->dom->input(\iw\html::TYPE_FILE, "image"), $this->dom->br(), $this->dom->button(\iw\html::TYPE_SUBMIT, null, "Vytvořit")));*//
	}



}