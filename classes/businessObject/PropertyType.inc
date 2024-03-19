<?php


namespace businessObject;


abstract class PropertyType
{


	protected mixed $value;


	public readonly bool $required;


	abstract protected function setValueCheck(mixed $value): bool;


	public function __construct(bool $required)
	{
		$this->required = $required;
	}


	/**
	 * @throws \businessObject\Exception
	 */
	public function set(mixed $value): void
	{
		if(!$this->setValueCheck($value))
			Error::PROPERTY_TYPE_ERROR-> throw("Property is not of required type");
		$this->value = $value;
	}


	public function get(): mixed
	{
		return $this->value;
	}


}