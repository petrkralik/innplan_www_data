<?php


namespace page;


class MenuItem implements \iw\dom\Component
{


	public string $id;
	public string $text;
	public string $link;
	private array $items = [];
	private static int $_menuIdCounter = 1;


	/**
	 * Constructs a new MenuItem instance.
	 *
	 * @param string            $text      The text of the menu item.
	 * @param MenuItem          ...$items  An array of MenuItem instances to be added as children.
	 *
	 * @throws \InvalidArgumentException If any of the provided items are not instances of MenuItem.
	 */
	public function __construct(?string $id, string $text, string $link, ...$items)
	{
		$this->id = $id ?? $this->getId();
		$this->text = $text;
		$this->link = $link;
		foreach ($items as $item) {
			$this->addItem($item);
		}
	}


	/**
	 * @param \iw\dom\Document|null $dom
	 *
	 * @return \DOMNode|array
	 * @throws \DOMException
	 * @throws \iw\dom\Exception
	 */
	public function getDomComponent(?\iw\dom\Document $dom): \DOMNode|array
	{
		$e = $dom->div(
			[
				\iw\html::A_ID => $this->id,
			],
			$dom->a(N, $this->link, $this->text)
		);
		if ($this->hasItems()) {
			$e->append($children = $dom->div([\iw\html::A_CLASS => "children"]));
			foreach ($this->items as $item)
				$children->appendChild($item->getSelfAsDOMNode());
		}

		return $e;
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


	/**
	 * Adds a child item to this menu item.
	 *
	 * @param MenuItem  $item  The menu item to add as a child.
	 */
	public function addItem(MenuItem $item): void
	{
		$this->items[] = $item;
	}


	/**
	 * Checks if this menu item has any child items.
	 *
	 * @return bool Returns true if this menu item has one or more child items, false otherwise.
	 */
	public function hasItems(): bool
	{
		return !empty($this->items);
	}


	/**
	 * Returns a generator that yields menu items.
	 *
	 * @return \Generator A generator that yields instances of MenuItem.
	 */
	public function getItemsIterator(): \Generator
	{
		foreach ($this->items as $item) {
			yield $item;
		}
	}


}