<?php


namespace businessObject;


enum Error: string
{


	case NO_OBJECT_LIKE_THIS = "NO_OBJECT_LIKE_THIS";
	case NONEXISTENT_PROPERTY = "NONEXISTENT_PROPERTY";
	case CLASS_MUST_IMPLEMENT_METHOD_SET = "CLASS_MUST_IMPLEMENT_METHOD_SET";
	case CLASS_MUST_IMPLEMENT_METHOD_GET = "CLASS_MUST_IMPLEMENT_METHOD_GET";
	case PROPERTY_TYPE_ERROR = "PROPERTY_TYPE_ERROR";
	case ITEM_MUST_BE_INSTANCE_OF_PROPERTY = "ITEM_MUST_BE_INSTANCE_OF_PROPERTY";
	case API_DATA_LOAD= "API_DATA_LOAD";
	case CANNOT_CREATE= "CANNOT_CREATE";
	case PROPERTY_NOT_SET = "PROPERTY_NOT_SET";
	case API_DATA_POST = "API_DATA_POST";
	case GENERAL = "GENERAL";


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