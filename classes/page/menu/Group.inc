<?php


namespace page\menu;


class Group extends Node implements NodeInterface
{


	public ?bool $expanded = null;
	private array $items= [];


	public function __construct(
		string $text,
		string $link,
		array $items,
		?string $id= null,
		?bool $expanded = null,
		?bool $disabled = null,
		?bool $invisible = null,
		?bool $notDisplayed = null
	) {
		parent::__construct($text, $link, $id, $disabled, $invisible, $notDisplayed);
		$this->expanded = $expanded;
	}


	public function itemsIterator(): \Generator
	{
		foreach ($this->items as $item)
			yield $item;
	}


	function getSelfAsDOMNode(): ?\DOMNode
	{
		// TODO: Implement getSelfAsDOMNode() method.
	}


}