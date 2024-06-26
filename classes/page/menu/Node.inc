<?php


namespace page\menu;


abstract class Node implements NodeInterface
{


	public string $id;
	public ?string $text;
	public ?string $link;
	public ?bool $disabled;
	public ?bool $invisible;
	public ?bool $notDisplayed;
	private static int $_menuIdCounter = 1;


	/**
	 */
	function __construct(?string $text, ?string $link, ?string $id= N, ?bool $disabled = null, ?bool $invisible = N, ?bool $notDisplayed = null)
	{
		$this->id = $id ?? $this->getId();
		$this->text = $text;
		$this->link = $link;
		$this->disabled = $disabled;
		$this->invisible = $invisible;
		$this->notDisplayed = $notDisplayed;
	}


	/**
	 * Generates and returns a unique ID for a menu item.
	 *
	 * This method concatenates a base string "menuItem" with an incrementing static counter
	 * to ensure each menu item receives a unique identifier. The counter is incremented with
	 * each call to this method.
	 *
	 * @return string A unique identifier for the menu item.
	 */
	private function getId(): string
	{
		return "menuItem" . self::$_menuIdCounter++;
	}


	protected function htmlClassList(): array {
		$list= ["node"];
		$list[]= match ($this::class) {
			Menu::class=> "menu",
			Group::class=> "group",
			Item::class=> "item"
		};
		if($this->disabled)
			$list[]= "disabled";
		if($this->invisible)
			$list[]= "invisible";

		return $list;
	}


}