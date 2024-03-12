<?php


namespace page;


abstract class Page extends \World
{


	abstract function getContent(\iw\DOMElementExtension $body): void;


}
