<?php


namespace businessObject;


abstract class Property
{


	private mixed $valueOriginal;
	private mixed $valueChanged;


	public readonly bool $required;
	public readonly bool $nullable;
	private bool $isSet = F;
	private bool $isChanged = F;


	abstract protected function setValueCheck(mixed $value): bool;


	public function __construct(bool $required = T, bool $nullable = F)
	{
		$this->required = $required;
		$this->nullable = $nullable;
	}


	public function isSet(): bool
	{
		return $this->isSet;
	}


	/**
	 * @throws Exception
	 */
	public function setValue(mixed $value): void
	{
		if (!$this->setValueCheck($value))
			Error::PROPERTY_TYPE_ERROR->throw("Property is not of required type");
		if ($this->isSet()) {
			$this->valueChanged = $value;
			$this->isChanged = T;
		} else {
			$this->valueOriginal = $value;
			$this->isSet = T;
		}
	}


	public function getValue(): mixed
	{
		return $this->isChanged ? $this->valueChanged : $this->valueOriginal;
	}


	public function getValueOriginal(): mixed
	{
		return $this->valueOriginal;
	}


	public function getValueChanged(): mixed
	{
		return $this->valueChanged;
	}


}