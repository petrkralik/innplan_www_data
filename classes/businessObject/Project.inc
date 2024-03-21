<?php


namespace businessObject;


/**
 * Represents a Project within a business object model. This class extends the BusinessObject
 * class and includes properties and methods specific to a project entity.
 *
 * Attributes:
 *
 * @property string       $name           Name of the project.
 * @property \DateTime    $dateStart      The start date of the project.
 * @property \DateTime    $dateEnd        The end date of the project.
 * @property int          $projectStateId The unique identifier for the project state.
 * @property ProjectState $projectState   An object representing the state of the project.
 * @property int          $clientId       The unique identifier for the client associated with the project.
 * @property Client       $client         An object representing the client associated with the project.
 */
class Project extends BusinessObject
{


	/**
	 * Constructs a new instance of the Project class.
	 *
	 * @param int $id The unique identifier of the project.
	 *
	 */
	public function __construct(int $id)
	{
		parent::__construct($id);
		$this->id = $id;
	}


	/**
	 * Provides the API URL for the current project. This URL is used to access or modify
	 * the project's data via a RESTful API.
	 *
	 * @return string The API URL specific to this project.
	 */
	#[\Override]
	public function apiUrl(): string
	{
		return "/v1/project/{$this->id}";
	}


	/**
	 * Defines a list of properties associated with the project. Each property is represented by
	 * a specific type that dictates how the property should be handled and validated.
	 *
	 * @return array An associative array where keys are property names and values are property types.
	 */
	#[\Override]
	public function propertyList(): array
	{
		$propProjectStateId= new PropertyInt(minimum: 1);
		$propClientId= new PropertyInt(minimum: 1);
		return [
			"name" => new PropertyString(),
			"dateStart" => new PropertyDate(F, T),
			"dateEnd" => new PropertyDate(F, T),
			"projectStateId" => $propProjectStateId,
			"projectState" => new PropertyObjectReferral($propProjectStateId, "ProjectState"),
			"clientId" => $propClientId,
			"client" => new PropertyObjectReferral($propClientId, "Client")
		];
	}


}
