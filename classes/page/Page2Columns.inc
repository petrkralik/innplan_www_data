<?php


namespace page;


/**
 * The Page2Columns abstract class extends Page to provide a specific layout with two columns.
 * This class defines the structure and functionality common to all pages with a two-column layout.
 */
abstract class Page2Columns extends Page
{


	private const string EID_HEADER = "pgHeader";

	private const string EID_CONTENT_LEFT = "pgContentLeft";

	private const string EID_CONTENT_MAIN = "pgContentMain";

	private const string EID_FOOTER = "pgContentFooter";


	private \iw\dom\Element $elementHeader;
	private \iw\dom\Element $elementLeft;
	private \iw\dom\Element $elementMain;
	private \iw\dom\Element $elementFooter;


	/**
	 * An abstract method that should be implemented by subclasses to provide the main content
	 * of the page located in the main column.
	 *
	 * @return \iw\dom\Element|null The DOM element representing the main content of the page.
	 */
	abstract function getContentMain(): ?\iw\dom\Element;


	/**
	 * Loads the content of the page by appending the loaded template to the provided body element,
	 * retrieving necessary elements, and populating specific areas of the page.
	 *
	 * @param   \iw\dom\Element  $body  The body element where the page content should be appended.
	 *
	 * @throws \iw\Exception If there are issues appending the content to the body.
	 */
	public function setContent(\iw\dom\Element $body): void
	{
		$body->appendChild($this->loadTemplate());
		$this->getElements();
		$this->elementLeft->append($this->getContentLeft());
		$this->elementMain->append($this->getContentMain());
	}


	/**
	 * Provides the content for the left column of the page. This default implementation
	 * returns a Menu object but can be overridden in subclasses to provide custom content.
	 *
	 * @return \iw\dom\NodeInterface|\iw\dom\Element|array The content for the left column, possibly null.
	 */
	function getContentLeft(): \iw\dom\NodeInterface|\iw\dom\Element|array
	{
		return new Menu(
			$this->documentProvider,
			"mainMenu",
			$this->doc->h2(N, "Projekty"),
			new MenuItem($this->doc, N, "Klienti", $this->urlBasePage(). "/client/list"),
			new MenuItem($this->doc, N, "Projekty", $this->urlBasePage(). "/project/list"),
			$this->doc->h2(N, "Číselníky"),
			new MenuItem($this->doc, N, "Zdroje", $this->urlBasePage(). "/resource/list"),
			new MenuItem($this->doc, N, "Role", $this->urlBasePage(). "/role/list"),
			new MenuItem($this->doc, N, "Stavy projektů", $this->urlBasePage(). "/project/state/list"),
			new MenuItem($this->doc, N, "Typy prací", $this->urlBasePage(). "/workType/list"),
		);
	}


	/**
	 * Retrieves and assigns the main elements of the page based on predefined IDs.
	 *
	 * @throws \page\Exception If any of the main elements cannot be found in the template.
	 */
	private function getElements(): void
	{
		$data = [
			"elementHeader" => self::EID_HEADER,
			"elementLeft"   => self::EID_CONTENT_LEFT,
			"elementMain"   => self::EID_CONTENT_MAIN,
			"elementFooter" => self::EID_FOOTER,
		];
		foreach ($data as $var => $element) {
			if (F == ($this->$var = $this->doc->getElementById($element)))
				Error::TEMPLATE_ELEMENT_MISSING->throw("The element ID \"$element\" hasn't been found in the template.");
		}
	}


	/**
	 * Loads the template for the two-column page from a predefined location.
	 *
	 * @return \iw\dom\Element The root element of the loaded template.
	 * @throws \iw\Exception If there are issues loading the template.
	 */
	private function loadTemplate(): \iw\dom\Element
	{
		return $this->doc->adopt(__DIR__."/resource/Page2Columns.template.html");
	}


}