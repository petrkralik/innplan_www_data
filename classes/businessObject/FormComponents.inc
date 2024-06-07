<?php


namespace businessObject;


abstract class FormComponents extends \iw\page\html\form\Components
{


	protected BusinessObject $businessObject;


	abstract public function buildFormComponents(): void;


	public function __construct(BusinessObject $businessObject) {
		$this->businessObject= $businessObject;
		$this->buildFormComponents();
	}


}