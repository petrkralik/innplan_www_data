<?php


namespace page;


abstract class Page2Columns extends Page
{


	abstract function getContentMain(\iw\DOMElementExtension $element): void;


	public function getContent(\iw\DOMElementExtension $body): void
	{
		$this->buildContent($body);
	}


	function getContentLeft()
	{

	}


	private function buildContent(\iw\DOMElementExtension $body) {
		$this->loadTemplate($body);
	}


	private function loadTemplate(\iw\DOMElementExtension $body) {
	}


}