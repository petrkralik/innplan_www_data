<?php


class DocumentProvider
{


	private \iw\DOMDocumentExtension $document;


	public function __construct(\iw\DOMDocumentExtension $document) {
		$this->document= $document;
	}


	public function document(): \iw\DOMDocumentExtension
	{

		return $this->document;
	}


}