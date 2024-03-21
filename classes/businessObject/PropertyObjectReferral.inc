<?php


namespace businessObject;


class PropertyObjectReferral extends Property
{


	public readonly string $classNameReferral;
	public readonly Property $propertyReferral;
	private BusinessObject $businessObject;
	private bool $businessObjectBuilt= F;


	public function __construct(Property $propertyReferral, string $classNameReferral)
	{
		parent::__construct(F);
		$this->propertyReferral = $propertyReferral;
		$this->classNameReferral = $classNameReferral;
	}


	#[\Override] protected function setValueCheck(mixed $value): bool
	{
		return T;
	}


	public function getObject(bool $forceBuild= F): ?BusinessObject
	{
		if(!$this->businessObjectBuilt) {
			$this->businessObject= new $this->classNameReferral($this->propertyReferral->getValue());
			$this->businessObjectBuilt= T;
		}

		return $this->businessObject;
	}


	public function reset(): void
	{
		unset($this->businessObject);
		$this->businessObjectBuilt= F;
	}


}