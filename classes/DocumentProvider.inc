<?php


class DocumentProvider
{


	private \iw\DOMDocumentExtension $document;


	public function __construct(\iw\DOMDocumentExtension $document) {
		$this->document= $document;
	}


	/**
	 * @throws \iw\Exception
	 */
	public function adopt(string $content, ?array $replacement= N, ?int $flags= N): \iw\DOMElementExtension
	{

		return $this->document->adopt($content, $replacement, $flags);
	}


}