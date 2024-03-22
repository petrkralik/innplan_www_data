<?php


namespace page;


/**
 * Abstract class Page providing the base structure for page objects in the application.
 * This class extends from the World class and utilizes document management and URI matching.
 */
abstract class Page extends \World
{


	/**
	 * @var \DocumentProvider An instance of DocumentProvider to manage document operations.
	 */
	private \DocumentProvider $documentProvider;

	/**
	 * @var array An array of URI matches for routing purposes.
	 */
	public array $uriMatches;

	/**
	 * @var \iw\dom\Document An instance of DOMDocumentExtension to handle document manipulations.
	 */
	protected \iw\dom\Document $doc;


	/**
	 * Abstract method to be implemented by subclasses to define the content of the page.
	 *
	 * @param   \iw\dom\Element  $body  The DOM element that should be used as the body of the page.
	 */
	abstract function getContent(\iw\dom\Element $body): void;


	/**
	 * Constructs a new Page object, initializing the document provider and URI matches.
	 *
	 * @param   \DocumentProvider  $documentProvider  The document provider instance to be used for document operations.
	 * @param   array              $uriMatches        An array of URI matches for the page, used for routing.
	 */
	public function __construct(\DocumentProvider $documentProvider, array $uriMatches)
	{
		parent::__construct();
		$this->doc = $documentProvider->document();
		$this->uriMatches = $uriMatches;
	}


}
