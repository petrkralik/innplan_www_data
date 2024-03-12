<?php


class Document extends \iw\Universe
{


	private DocumentElements $elements;
	private RequestClassResolver $resolver;
	private \iw\DOMDocumentExtension $content;


	public function __construct(RequestClassResolver $resolver) {
		parent::__construct();
		$this->resolver= $resolver;
		$this->content= new \iw\DOMDocumentExtension("UTF-8");
		$this->elements= new DocumentElements($this->content);
	}


	public function display(): void
	{
		$page= $this->resolver->getPageClass();
	}



}