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
	 * @var PageFiles Manages the inclusion and iteration of CSS files for the page.
	 * This property is an instance of the PageCSS class, which provides methods
	 * to add CSS files and iterate over them, handling both relative and absolute paths.
	 */
	public PageFiles $css;

	/**
	 * Instance of PageJS that manages the inclusion and organization of JavaScript files for the page.
	 * This property allows adding, managing, and iterating over JavaScript files to be included in the page.
	 * It handles both relative and absolute paths and ensures that each JavaScript file is included only once.
	 *
	 * @var PageFiles Manages JavaScript file links for the web page.
	 */
	public PageFiles $javascript;


	/**
	 * Abstract method to be implemented by subclasses to define the content of the page.
	 *
	 * @param   \iw\dom\Element  $body  The DOM element that should be used as the body of the page.
	 */
	abstract function setContent(\iw\dom\Element $body): void;


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
		$this->css = new PageFiles();
		$this->javascript = new PageFiles();
		$this->css->setRoot("/file/stylesheet/");
		$this->css->addFile("main.css");
	}


}
