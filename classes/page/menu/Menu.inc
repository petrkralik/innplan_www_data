<?php


namespace page\menu;


/**
 * The Menu class represents a dynamic menu structure in a web document,
 * allowing the addition of various elements that can be rendered as part of the menu.
 */
class Menu implements \iw\dom\NodeInterface
{

	/**
	 * @var \DocumentProvider The document in which the menu will be created, allowing for element creation and manipulation.
	 */
	private \DocumentProvider $documentProvider;

	/**
	 * @var string A unique identifier for the menu, used for assigning an ID to the menu's DOM element.
	 */
	public readonly string $id;

	/**
	 * @var array A collection of items that are part of the menu. Each item must either be a DOMNode or implement NodeInterface.
	 */
	private array $items = [];


	/**
	 * Constructs a new Menu object, initializing with an optional array of items.
	 *
	 * @param   \DocumentProvider  $documentProvider  The document context for the menu.
	 * @param   string             $id                The unique identifier for the menu.
	 * @param   mixed              ...$items          Optional initial items to include in the menu.
	 *
	 * @throws \page\Exception
	 */
	public function __construct(\DocumentProvider $documentProvider, string $id, ...$items)
	{
		$this->documentProvider = $documentProvider;
		$this->id= $id;
		$this->addItems(...$items);
	}


	/**
	 * Adds one or more items to the menu. Each item must be compatible with DOM operations, either being a DOMNode or implementing NodeInterface.
	 *
	 * @param mixed ...$items The items to add to the menu.
	 * @throws \page\Exception If an item does not comply with the expected types.
	 */
	public function addItems(...$items): void
	{
		foreach ($items as $item) {
			if($item instanceof \DOMNode || $item instanceof \iw\dom\NodeInterface)
				$items[]= $item;
			else
				\page\Error::GENERAL->throw("Given item must be inheritor of \DOMNode or must implement \iw\dom\NodeInterface");
		}
	}


	/**
	 * Converts the menu into a DOMNode, which can be embedded within the DOM of the page. The menu is wrapped in a <div> element with a unique ID.
	 *
	 * @return \DOMNode|null The DOM node representation of the menu or null if the menu is empty.
	 */
	function getSelfAsDOMNode(): ?\DOMNode
	{
		if(empty($this->items))
			return \N;

		return $this->documentProvider->document()->div(
			[
				\iw\html::A_ID=> $this->id,
				\iw\html::A_CLASS=> "menu"
			],
			$this->items
		);
	}


}