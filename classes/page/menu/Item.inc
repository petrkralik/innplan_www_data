<?php


namespace page\menu;


class Item extends Node
{


	/**
	 * @throws \DOMException
	 */
	function getDomComponent(\iw\dom\Document $dom): \DOMNode|array
	{
		return $dom->div(
			[
				\iw\html::A_ID=> $this->id,
				\iw\html::A_CLASS=> implode(" ", $this->htmlClassList())
			],
			$dom->a(
				N,
				$this->link,
				$this->text
			)
		);
	}


}