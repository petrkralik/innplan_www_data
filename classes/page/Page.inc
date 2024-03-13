<?php


namespace page;


abstract class Page extends \World
{


	private \DocumentProvider $documentProvider;
	private array $uriMatches;
	protected \iw\DOMDocumentExtension $doc;


	abstract function getContent(\iw\DOMElementExtension $body): void;


	public function __construct(\DocumentProvider $documentProvider, array $uriMatches) {
		parent::__construct();
		$this->doc= $documentProvider->document();
		$this->uriMatches= $uriMatches;
	}


	protected function uriMatches(): array
	{

		return $this->uriMatches;
	}


}
