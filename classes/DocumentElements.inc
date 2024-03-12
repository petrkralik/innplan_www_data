<?php


class DocumentElements extends \iw\Universe {


	public \iw\DOMElementExtension $html;
	public \iw\DOMElementExtension $head;
	public \iw\DOMElementExtension $body;


	public function __construct(\iw\DOMDocumentExtension $doc) {
		parent::__construct();
		$this->build($doc);
	}


	private function build(\iw\DOMDocumentExtension $doc): void
	{
		$doc-> appendChild(
			$this-> html= $doc-> DOMElement(iw\html::E_HTML, N,
				$this-> head= $doc-> DOMElement(iw\html::E_HEAD),
				$this-> body= $doc-> DOMElement(iw\html::E_BODY)
			)
		);
	}


}