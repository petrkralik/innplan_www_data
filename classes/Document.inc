<?php


/**
 * The Document class provides a structure for creating, manipulating, and rendering an HTML document.
 * It encapsulates the creation of the fundamental HTML elements and manages the addition of CSS files.
 */
class Document extends \iw\Universe
{


	/**
	 * @var DocumentElements Holds instances of the main HTML elements (html, head, body) for easy access and manipulation.
	 */
	private DocumentElements $elements;

	/**
	 * @var RequestClassResolver A resolver used to determine the appropriate page class based on the current request.
	 */
	private RequestClassResolver $resolver;

	/**
	 * @var \iw\dom\Document Represents the DOM document and provides methods for DOM manipulation.
	 */
	private \iw\dom\Document $document;


	/**
	 * Constructor initializes the document, document elements, and class resolver.
	 *
	 * @throws \DOMException If there is an error during the document or elements initialization.
	 */
	public function __construct()
	{
		parent::__construct();
		$this->document= new \iw\dom\Document($this->cfg["charset"]);
		$this->elements= new DocumentElements($this->document);
		$this->resolver= new RequestClassResolver();
	}


	/**
	 * Generates the final HTML content by setting the content for the page, managing CSS files,
	 * and outputting the HTML string.
	 *
	 * @throws ReflectionException If there is an error during page class resolution.
	 * @throws RequestClassResolverException If there is an error during the request class resolution.
	 * @throws \DOMException If there is an error during DOM manipulation or CSS file management.
	 */
	public function display(): void
	{
		$page= $this->resolver->getPageClass(new DocumentProvider($this->document));
		$page->setContent($this->elements->body);
		$this->manageCssFiles($page);
		$this->manageJsFiles($page);
		echo iw\html::DOCTYPE_5. EOL. $this-> document-> saveHTML();
	}


	/**
	 * Manages the inclusion of CSS files into the document by appending <link> elements to the <head>.
	 *
	 * @param \page\Page $page The page instance from which CSS files are retrieved and managed.
	 *
	 * @throws \DOMException If there is an error during the creation or appending of <link> elements.
	 */
	private function manageCssFiles(\page\Page $page): void
	{
		foreach ($page->css->filesIterator() as $file)
			$this->elements->head->appendChild(
				$this->document->element(\iw\html::E_LINK,
					[
						\iw\html::A_REL => 'stylesheet',
						\iw\html::A_TYPE => 'text/css',
						\iw\html::A_HREF => $file
					]
				)
			);
	}


	/**
	 * Manages the inclusion of JavaScript files into the document by appending <script> elements to the <body>.
	 * Iterates over the JavaScript files provided by the PageJS instance associated with the page
	 * and appends each one as a <script> element to the body of the document.
	 *
	 * @param \page\Page $page The page instance from which JavaScript files are retrieved and managed.
	 *
	 * @throws \DOMException If there is an error during the creation or appending of <script> elements.
	 */
	private function manageJsFiles(\page\Page $page): void
	{
		foreach ($page->javascript->filesIterator() as $file)
			$this->elements->body->appendChild(
				$this->document->element(\iw\html::E_SCRIPT,
					[
						\iw\html::A_TYPE => 'text/javascript',
						\iw\html::A_SRC  => $file,
					]
				)
			);
	}


}