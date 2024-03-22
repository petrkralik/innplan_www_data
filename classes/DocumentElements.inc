<?php


class DocumentElements extends \iw\Universe {


	public \iw\dom\Element $html;
	public \iw\dom\Element $head;
	public \iw\dom\Element $body;


	/**
	 * @throws DOMException
	 */
	public function __construct(\iw\dom\Document $doc) {
		parent::__construct();
		$this->build($doc);
	}


	/**
	 * @throws DOMException
	 */
	private function build(\iw\dom\Document $doc): void
	{
		$doc-> appendChild(
			$this-> html= $doc-> element(\iw\html::E_HTML, N,
				$this-> head= $doc-> element(\iw\html::E_HEAD),
				$this-> body= $doc-> element(\iw\html::E_BODY)
			)
		);
	}


}