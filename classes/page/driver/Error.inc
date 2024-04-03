<?php


namespace page\driver;


enum Error: string
{


	/**
	 * This case occurs when a class does not exist in the application.
	 */
	case RESOLVER_CLASS_NOT_EXISTS = "RESOLVER_CLASS_NOT_EXISTS";

	/**
	 * This case is triggered when a class is not a successor (child) of the required parent class.
	 */
	case RESOLVER_CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT = "RESOLVER_CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT";


	/**
	 * @throws Exception
	 */
	public function throw(?string $message = N, ?string $description = N, ?\Throwable $previous = N, ?int $flags = N, ?array $additionalInfo = N)
	{
		throw new Exception($this, $message, $description, $previous, $flags, $additionalInfo);
	}


}