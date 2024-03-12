<?php


class Document extends \iw\Universe
{


	public \page\Page $page;
	public DocumentElements $elements;
	private \iw\DOMDocumentExtension $content;


	public function __construct(\page\Page $page) {
		parent::__construct();
		$this->elements= new DocumentElements($this->content= new \iw\DOMDocumentExtension("UTF-8"));
	}


	public function display(): void
	{
		var_dump($this->elements->body);
	}



}