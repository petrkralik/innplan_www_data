<?php


namespace businessObject;


abstract class Property
{


	protected mixed $value;
	proteced


	public readonly bool $required;
	public readonly bool $nullable;
	private bool $isSet= F;
	private bool $isChanged= F;


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
	 * @throws \businessObject\Exception
	 */
	public function set(mixed $value): void
	{
		if (! $this->setValueCheck($value))
			Error::PROPERTY_TYPE_ERROR->throw("Property is not of required type");
		if($this->isSet()) {
			change
		}

		$this->value = $value;
	}


	public function get(): mixed
	{
		return $this->value;
	}




}