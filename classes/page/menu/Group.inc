<?php


namespace page\menu;


class Group extends Node implements NodeInterface
{


	public ?bool $expanded = null;
	protected array $items= [];


	public function __construct(
		?string $text= N,
		?string $link= N,
		?string $id= N,
		?bool $disabled = null,
		?bool $invisible = null,
		?bool $notDisplayed = null,
		?bool $expanded= null,
		array $items= []
	) {
		parent::__construct($text, $link, $id, $disabled, $invisible, $notDisplayed);
		$this->expanded = $expanded;
		if($this)
			foreach ($items as $item)
				$this->addItem($item);
	}


	public function addItem(NodeInterface $item): void
	{
		$this->items[]= $item;
	}


	public function itemsIterator(): \Generator
	{
		foreach ($this->items as $item)
			yield $item;
	}


	/**
	 * @throws \DOMException
	 */
	function getSelfAsDOMNode(): ?\DOMNode
	{
		return $this->dom->div(
			[
				\iw\html::A_ID=> $this->id,
				\iw\html::A_CLASS=> implode(" ", $this->htmlClassList())
			],
			$this->link? $this->dom->a(N, $this->link, $this->text): $this->text,
			$this->items
		);
	}


}