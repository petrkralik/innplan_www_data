<?php


namespace page;


abstract class Page2Columns extends Page
{



	abstract function getContentMain(\iw\DOMElementExtension $body): void;


	public function getContent(\iw\DOMElementExtension $body): void
	{
		$this->buildContent($body);
	}


	function getContentLeft() {}


	private function buildContent(\iw\DOMElementExtension $body): void
	{
		$this->loadTemplate($body);
	}


	private function loadTemplate(\iw\DOMElementExtension $body): void
	{
		$this->getDocumentProvider()->adopt(__DIR__."/resource/Page2Columns.template.html");
	}


}