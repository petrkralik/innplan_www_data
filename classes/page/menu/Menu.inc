<?php


namespace page\menu;


/**
 * The Menu class represents a dynamic menu structure in a web document,
 * allowing the addition of various elements that can be rendered as part of the menu.
 */
class Menu extends Group
{


	public function __construct(
		string $text,
		?string $link = N,
		?string $id = N,
		?bool $disabled = null,
		?bool $invisible = null,
		?bool $notDisplayed = null,
		?bool $expanded = null,
		array $items = []
	) {
		parent::__construct($text, $link, $id, $disabled, $invisible, $notDisplayed, $expanded, $items);
	}


}