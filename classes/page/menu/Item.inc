<?php


namespace page\menu;


class Item extends Node
{


	/**
	 * @throws \DOMException
	 */
	function getSelfAsDOMNode(): ?\DOMNode
	{
		return $this->dom->div(
			[
				\iw\html::A_ID=> $this->id,
				\iw\html::A_CLASS=> "node item"
			],
			$this->dom->a(
				N,
				$this->link,
				$this->text
			)
		);
	}


}