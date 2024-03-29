<?php


namespace businessObject;


/**
 * Represents a Project within a business object model. This class extends the BusinessObject
 * class and includes properties and methods specific to a project entity.
 *
 * Attributes:
 *
 * @property PropertyString $name           Name of the project.
 * @property PropertyDate   $dateStart      The start date of the project.
 * @property PropertyDate   $dateEnd        The end date of the project.
 * @property PropertyInt    $projectStateId The unique identifier for the project state.
 * @property ProjectState   $projectState   An object representing the state of the project.
 * @property PropertyInt    $clientId       The unique identifier for the client associated with the project.
 * @property Client         $client         An object representing the client associated with the project.
 */
class Project extends BusinessObject
{


	/**
	 * Provides the API URL for the current project. This URL is used to access or modify
	 * the project's data via a RESTful API.
	 *
	 * @return string The API URL specific to this project.
	 * @throws Exception
	 */
	#[\Override] public function apiUrlGet(): string
	{
		if (!$this->id)
			Error::GENERAL->throw("Object must exist.");

		return $this->urlBaseApi() . "/v1/project/{$this->id}";
	}


	/**
	 * @throws Exception
	 */
	public function apiUrlCreate(): string
	{
		if (!$this->clientId->isSet())
			Error::GENERAL->throw("Attribute clientId must be set");

		return $this->urlBaseApi() . "/v1/client/{$this->clientId->getValue()}/project/";
	}


	/**
	 * Implementation of the abstract method to specify
	 * the properties required for the create() method in the Project class.
	 *
	 * @return array List of Property objects required for creating a Project, excluding 'clientId'.
	 */
	#[\Override] public function propertyListForCreate(): array
	{
		$requiredPropertiesForCreate = [];
		foreach ($this->properties as $propertyName => $propertyObject)
			if ($propertyName !== 'clientId')
				$requiredPropertiesForCreate[$propertyName] = $propertyObject;

		return $requiredPropertiesForCreate;
	}


	/**
	 * Defines a list of properties associated with the project. Each property is represented by
	 * a specific type that dictates how the property should be handled and validated.
	 *
	 * @return array An associative array where keys are property names and values are property types.
	 */
	#[\Override] public function propertyList(): array
	{
		$propProjectStateId = new PropertyInt(minimum: 1);
		$propClientId = new PropertyInt(minimum: 1);

		return [
			"name" => new PropertyString(),
			"dateStart" => new PropertyDate(F, T),
			"dateEnd" => new PropertyDate(F, T),
			"projectStateId" => $propProjectStateId,
			"projectState" => new PropertyObjectReferral($propProjectStateId, __NAMESPACE__ . "\ProjectState"),
			"clientId" => $propClientId,
			"client" => new PropertyObjectReferral($propClientId, __NAMESPACE__ . "\Client")
		];
	}


}
