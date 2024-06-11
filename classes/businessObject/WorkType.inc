<?php


namespace businessObject;


/**
 * Represents a Work Type entity.
 *
 * @property \businessObject\property\PropertyString $name
 * @property \businessObject\property\PropertyInt    $workTypeSeniorityId
 * @property \businessObject\property\PropertyBool   $disabled
 * @property \businessObject\property\PropertyString $description
 */
class WorkType extends BusinessObject
{


	public function apiUrlCreate(): string
	{
		return urlBaseAPI."/v1/workType";
	}


	/**
	 * @throws Exception
	 */
	public function apiUrlGet(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBaseAPI."/v1/workType/{$this->id}";
	}


	/**
	 * @throws Exception
	 */
	public function apiUrlEdit(): string
	{
		return $this->apiUrlGet();
	}


	/**
	 * @throws Exception
	 */
	public function apiUrlDelete(): string
	{
		return $this->apiUrlGet();
	}


	protected function propertyList(): array
	{
		return [
			\entity\WorkType::ATTRIBUTE_NAME         => new \businessObject\property\PropertyString(),
			\entity\WorkType::ATTRIBUTE_DESCRIPTION  => new \businessObject\property\PropertyString(false, true),
			\entity\WorkType::ATTRIBUTE_SENIORITY_ID => new \businessObject\property\PropertyInt(),
			\entity\WorkType::ATTRIBUTE_DISABLED     => new \businessObject\property\PropertyBool(false, true),
		];
	}


	protected function propertyListForCreation(): array
	{
		return $this->properties;
	}


	/**
	 * @throws \businessObject\Exception
	 */
	public function urlPageDetail(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBasePage."/workType/{$this->id}";
	}


	public function urlPageNew(): string
	{
		return urlBasePage."/workType/new";
	}


	/**
	 * @throws \businessObject\Exception
	 */
	public function urlPageEdit(): string
	{
		if (! $this->id)
			Error::GENERAL->throw("Object must exist.");

		return urlBasePage."/workType/new";
	}


	public function getFormComponents(\page\Page $controlObject): \iw\page\html\form\Components
	{
		if (! isset($this->formComponents))
			$this->formComponents = new WorkTypeFormComponents($controlObject);

		return $this->formComponents;
	}


}