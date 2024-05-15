<?php


namespace businessObject;


enum Error: string
{


	/**
	 * Used when no object matching the given identifier or parameters is found.
	 * Commonly thrown during API data fetches.
	 * */
	case NO_OBJECT_LIKE_THIS = "NO_OBJECT_LIKE_THIS";

	/**
	 * Used when a non-existent property is attempted to be accessed or modified.
	 * Commonly thrown during property assignment or retrieval.
	 */
	case NONEXISTENT_PROPERTY = "NONEXISTENT_PROPERTY";

	/**
	 * Used when a class does not implement the 'set' method.
	 * Commonly thrown during object manipulation operations.
	 */
	case CLASS_MUST_IMPLEMENT_METHOD_SET = "CLASS_MUST_IMPLEMENT_METHOD_SET";

	/**
	 * Used when a class does not implement the 'get' method.
	 * Commonly thrown during object manipulation operations.
	 */
	case CLASS_MUST_IMPLEMENT_METHOD_GET = "CLASS_MUST_IMPLEMENT_METHOD_GET";

	/**
	 * Used when a property value does not match the required data type.
	 * Commonly thrown during property value assignment.
	 */
	case PROPERTY_TYPE_ERROR = "PROPERTY_TYPE_ERROR";

	/**
	 * Used when an item is expected to be an instance of 'Property' but it's not.
	 * Commonly thrown during the 'setProperty' operation.
	 */
	case ITEM_MUST_BE_INSTANCE_OF_PROPERTY = "ITEM_MUST_BE_INSTANCE_OF_PROPERTY";

	/**
	 * Used when API data cannot be loaded.
	 * Commonly thrown during API data fetch operations.
	 */
	case API_DATA_LOAD = "API_DATA_LOAD";

	/**
	 * Used when an object cannot be created.
	 * Commonly thrown during the object creation phase.
	 */
	case CANNOT_CREATE = "CANNOT_CREATE";

	/**
	 * Used when a property is not set but was expected to be.
	 * Commonly thrown during data processing and manipulation.
	 */
	case PROPERTY_NOT_SET = "PROPERTY_NOT_SET";

	/**
	 * Used when API data posting fails.
	 * Commonly thrown during API data update operations.
	 */
	case API_DATA_POST = "API_DATA_POST";

	/**
	 * Used as a general error flag for miscellaneous situations.
	 */
	case GENERAL = "GENERAL";

	/**
	 * Used when an API response is missing the 'id' field.
	 * Commonly thrown during the API's response parsing.
	 */
	case API_RESPONSE_MISSING_ID = "API_RESPONSE_MISSING_ID";

	/**
	 * Used when an attempt is made to remove a property that cannot be erased.
	 * Commonly thrown during data cleanup operations.
	 */
	case PROPERTY_CANNOT_BE_ERASED = "PROPERTY_CANNOT_BE_ERASED";
	/**
	 * Used when an object is already initiated but another initiation is attempted.
	 * Commonly thrown during the duplicate object initiation process.
	 */
	case OBJECT_ALREADY_INITIATED = "OBJECT_ALREADY_INITIATED";

	/**
	 * Used when a property is already initialized but an attempt is made to
	 * reinitialize it. Thrown commonly during property reinitialization attempts.
	 */
	case PROPERTY_ALREADY_INITIALIZED = "PROPERTY_ALREADY_INITIALIZED";

	/**
	 * Used when an attempt is made to access a property that has not been
	 * initialized yet. Frequently thrown during property access operations.
	 */
	case PROPERTY_NOT_INITIALIZED = "PROPERTY_NOT_INITIALIZED";


	/**
	 * @throws Exception
	 */
	public function throw(
		?string $message = N,
		?string $description = N,
		?\Throwable $previous = N,
		?int $flags = N,
		?array $additionalInfo = N
	): void {
		throw new Exception($this, $message, $description, $previous, $flags, $additionalInfo);
	}



}