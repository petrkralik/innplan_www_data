<?php


class DocumentProvider
{


	private \iw\dom\Document $document;


	public function __construct(\iw\dom\Document $document) {
		$this->document= $document;
	}


	public function document(): \iw\dom\Document
	{

		return $this->document;
	}


}