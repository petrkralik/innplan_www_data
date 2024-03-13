<?php


namespace page;


abstract class Page extends \World
{


	private \DocumentProvider $documentProvider;
	private array $uriMatches;


	abstract function getContent(\iw\DOMElementExtension $body): void;


	public function __construct(\DocumentProvider $documentProvider, array $uriMatches) {
		parent::__construct();
		$this->documentProvider= $documentProvider;
		$this->uriMatches= $uriMatches;
	}


	protected function documentProvider(): \DocumentProvider
	{

		return $this->documentProvider;
	}


	protected function getUriMatches(): array
	{

		return $this->uriMatches;
	}


}
