<?php


namespace businessObject\property;


enum Error: string
{


	/**
	 * Used when an attempt is made to remove a property that cannot be erased.
	 * Commonly thrown during data cleanup operations.
	 */
	case PROPERTY_CANNOT_BE_ERASED = "PROPERTY_CANNOT_BE_ERASED";

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