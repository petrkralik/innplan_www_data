<?php


namespace businessObject;


/**
 * PropertyInt is a subclass of Property designed to handle integer values,
 * providing additional validation to ensure the value falls within an optional specified range.
 */
class PropertyInt extends Property
{


	/**
	 * The minimum value that this property can hold. If set, any value set to this property
	 * must be equal or greater than this minimum value.
	 *
	 * @var ?int
	 */
	public readonly ?int $minimum;

	/**
	 * The maximum value that this property can hold. If set, any value set to this property
	 * must be equal or less than this maximum value.
	 *
	 * @var ?int
	 */
	public readonly ?int $maximum;


	/**
	 * Constructs a PropertyInt instance with specified constraints.
	 *
	 * @param bool $required Specifies if the property is required.
	 * @param bool $nullable Specifies if the property can accept null values.
	 * @param ?int $minimum  The minimum value the property can hold.
	 * @param ?int $maximum  The maximum value the property can hold.
	 */
	public function __construct(bool $required = true, bool $nullable = false, ?int $minimum = null, ?int $maximum = null)
	{
		parent::__construct($required, $nullable);
		$this->minimum = $minimum;
		$this->maximum = $maximum;
	}


	/**
	 * Validates that the provided value is an integer and, if minimum and maximum values are set,
	 * checks that the value falls within the specified range.
	 *
	 * @param mixed $value The value to validate.
	 *
	 * @return bool True if the value is an integer and within the specified range, false otherwise.
	 */
	protected function valueCheckOnSet(mixed $value): bool
	{
		if (is_int($value)) {
			if ($this->minimum !== null && $value < $this->minimum)
				return false;
			if ($this->maximum !== null && $value > $this->maximum)
				return false;

			return true;
		}

		return false;
	}


}
