<?php


namespace page;


abstract class Page2Columns extends Page
{


	private const string EID_HEADER = "pgHeader";

	private const string EID_CONTENT_LEFT = "pgContentLeft";

	private const string EID_CONTENT_MAIN = "pgContentMain";

	private const string EID_FOOTER = "pgContentFooter";


	private \iw\DOMElementExtension $elementHeader;
	private \iw\DOMElementExtension $elementLeft;
	private \iw\DOMElementExtension $elementMain;
	private \iw\DOMElementExtension $elementFooter;


	abstract function getContentMain(): \iw\DOMElementExtension;


	/**
	 * @throws \iw\Exception
	 */
	public function getContent(\iw\DOMElementExtension $body): void
	{
		$body->appendChild($this->loadTemplate());
		$this->getElements();
		$this->getContentLeft($this->elementLeft);
		$this->getContentMain($this->elementMain);
	}


	function getContentLeft(\iw\DOMElementExtension $element): void {
	}


	/**
	 * @throws \page\Exception
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
			if (F == ($this->$var = $this->doc->getElementById($element))) {
				Error::TEMPLATE_ELEMENT_MISSING->throw("The element ID \"$element\" hasn't been found in the template.");
			}
		}
	}


	/**
	 * @throws \iw\Exception
	 */
	private function loadTemplate(): \iw\DOMElementExtension
	{
		return $this->doc->adopt(__DIR__."/resource/Page2Columns.template.html");
	}


}