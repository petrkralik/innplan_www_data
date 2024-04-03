<?php


namespace page\menu;


class Item extends Node
{



	function getSelfAsDOMNode(): ?\DOMNode
	{
		return $this->dom->div(
			[
				\iw\html::A_CLASS=> "item"
			],
			$this->dom->a(
				N,
				$this->link,
				$this->text
			)
		);
	}


}