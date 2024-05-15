<?php


namespace businessObject;


/**
 * The PropertyObjectReferral class extends the Property class to enable object-oriented references
 * within the business object model. It allows properties to refer to entire business objects,
 * creating a link between the property and the business object it references.
 */
class PropertyObjectReferral extends \businessObject\property\Property
{


	/**
	 * The class name of the business object to which this property refers. This class name is used
	 * to instantiate the business object when needed.
	 *
	 * @var string
	 */
	public readonly string $classNameReferral;

	/**
	 * The property instance that this PropertyObjectReferral is linked to. Changes to the value
	 * of the referred property can affect the state of this PropertyObjectReferral.
	 *
	 * @var \businessObject\property\Property
	 */
	public readonly \businessObject\property\Property $propertyReferral;

	/**
	 * The business object instance that is referred to by this PropertyObjectReferral. This instance
	 * is lazily instantiated when first accessed through getObject() method.
	 *
	 * @var BusinessObject
	 */
	private BusinessObject $businessObject;

	/**
	 * A flag indicating whether the business object has been instantiated.
	 *
	 * @var bool
	 */
	private bool $businessObjectBuilt = false;


	/**
	 * Constructs a new instance of PropertyObjectReferral.
	 *
	 * @param   \businessObject\property\Property  $propertyReferral   The property that holds the reference.
	 * @param   string                             $classNameReferral  The class name of the business object to which this property refers.
	 *
	 * @throws \businessObject\property\Exception
	 */
	public function __construct(\businessObject\property\Property $propertyReferral, string $classNameReferral)
	{
		parent::__construct(false);
		$this->propertyReferral = $propertyReferral;
		$this->classNameReferral = $classNameReferral;
		$this->propertyReferral->addReferral($this);
	}


	/**
	 * Always returns true as the value check is not applicable for PropertyObjectReferral.
	 *
	 * @param mixed $value The value to check (unused in this context).
	 *
	 * @return bool Always true.
	 */
	#[\Override]
	protected function valueCheckOnSet(mixed $value): bool
	{
		return true;
	}


	/**
	 * Retrieves the business object instance that this PropertyObjectReferral refers to.
	 * If the instance has not been created yet, it is instantiated.
	 *
	 * @param   bool  $forceBuild  Forces the reconstruction of the business object, even if it's already built.
	 *
	 * @return BusinessObject|null The business object instance or null if it cannot be instantiated.
	 * @throws \businessObject\property\Exception
	 */
	public function getObject(bool $forceBuild = false): ?BusinessObject
	{
		if (!$this->businessObjectBuilt || $forceBuild) {
			$this->businessObject = new $this->classNameReferral($this->propertyReferral->getValue());
			$this->businessObjectBuilt = true;
		}

		return $this->businessObject;
	}


	/**
	 * Resets the state of this PropertyObjectReferral, clearing the cached business object instance.
	 * This is typically called when the underlying property value changes.
	 */
	public function emptyObject(): void
	{
		unset($this->businessObject);
		$this->businessObjectBuilt = false;
	}


}
