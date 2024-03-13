<?php


namespace page;


abstract class Page extends \World
{


	abstract function getContent(\iw\DOMElementExtension $body): void;


	public function __construct(array $args) {
		parent::__construct();
		var_dump($args);
	}


}
