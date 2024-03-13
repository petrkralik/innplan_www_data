<?php


class Document extends \iw\Universe
{


	private DocumentElements $elements;
	private RequestClassResolver $resolver;
	private \iw\DOMDocumentExtension $document;


	public function __construct() {
		parent::__construct();
		$this->document= new \iw\DOMDocumentExtension("UTF-8");
		$this->elements= new DocumentElements($this->document);
		$this->resolver= new RequestClassResolver();
	}


	/**
	 * @throws ReflectionException
	 * @throws RequestClassResolverException
	 */
	public function display(): void
	{
		$this->resolver->getPageClass(new DocumentProvider($this->document))->getContent($this->elements->body);
		$content=
			iw\html::DOCTYPE_5. EOL.
			$this-> document-> saveHTML();
		echo $content;
	}


}