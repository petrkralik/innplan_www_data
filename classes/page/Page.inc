<?php


namespace page;


abstract class Page extends \World
{


	private \DocumentProvider $documentProvider;


	abstract function getContent(\iw\DOMElementExtension $body): void;


	public function __construct(\DocumentProvider $documentProvider, array $args) {
		parent::__construct();
		$this->documentProvider= $documentProvider;
		var_dump($args);
	}


	protected function getDocumentProvider(): \DocumentProvider
	{

		return $this->documentProvider;
	}


}
