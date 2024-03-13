<?php


namespace page;


abstract class Page2Columns extends Page
{



	abstract function getContentMain(\iw\DOMElementExtension $body): void;


	public function getContent(\iw\DOMElementExtension $body): void
	{
		$body->appendChild($this->buildContent());
	}


	function getContentLeft() {

	}


	private function buildContent(): \iw\DOMElementExtension
	{
		return $this->loadTemplate();
	}


	private function loadTemplate(): \iw\DOMElementExtension
	{

		return $this->getDocumentProvider()->adopt(__DIR__."/resource/Page2Columns.template.html");
	}


}