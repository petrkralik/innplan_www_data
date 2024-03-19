<?php


namespace businessObject;


class PropertyInt extends PropertyType
{


	public readonly ?int $minimum;
	public readonly ?int $maximum;


	public function __construct(bool $required, ?int $minimum = N, ?int $maximum = N)
	{
		parent::__construct($required);
		$this->minimum = $minimum;
		$this->maximum = $maximum;
	}


	#[\Override] protected function setValueCheck(mixed $value): bool
	{
		if (is_int($value)) {
			if (($this->minimum !== null) && ($value < $this->minimum))
				return F;
			if (($this->maximum !== null) && ($value > $this->maximum))
				return F;

			return T;
		}

		return F;
	}


}