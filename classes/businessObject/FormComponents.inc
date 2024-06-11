<?php


namespace businessObject;


abstract class FormComponents extends \iw\page\html\form\Components
{


	protected \page\Page $controlObject;


	abstract public function buildFormComponents(): void;


	public function __construct(\page\Page $controlObject) {
		$this->controlObject= $controlObject;
		$this->buildFormComponents();
	}


}