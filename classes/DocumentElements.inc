<?php


/**
 * The DocumentElements class provides easy access to the main elements of an HTML document: html, head, and body.
 * It initializes these elements upon construction, using a provided iw\dom\Document instance.
 */
class DocumentElements extends \iw\Universe
{


	/**
	 * @var \iw\dom\Element Represents the <html> element of the document.
	 */
	public \iw\dom\Element $html;

	/**
	 * @var \iw\dom\Element Represents the <head> element of the document.
	 */
	public \iw\dom\Element $head;

	/**
	 * @var \iw\dom\Element Represents the <body> element of the document.
	 */
	public \iw\dom\Element $body;


	/**
	 * Constructs the DocumentElements object, initializing the html, head, and body elements.
	 *
	 * @param   \iw\dom\Document  $doc  The Document object to which the elements belong.
	 *
	 * @throws DOMException If there is an error during the creation of the elements.
	 */
	public function __construct(\iw\dom\Document $doc)
	{
		parent::__construct();
		$this->build($doc);
	}


	/**
	 * Creates and appends the main HTML elements (html, head, body) to the provided document.
	 *
	 * @param \iw\dom\Document $doc The Document object to which the elements will be appended.
	 * @throws DOMException If there is an error during the creation or appending of the elements.
	 */
	private function build(\iw\dom\Document $doc): void
	{
		$doc->appendChild($this->html =
			$doc->element(\iw\html::E_HTML, N, $this->head = $doc->element(\iw\html::E_HEAD), $this->body = $doc->element(\iw\html::E_BODY)));
	}


}