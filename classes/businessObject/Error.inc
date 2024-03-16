<?php


namespace businessObject;


enum Error: string
{


	case NO_OBJECT_LIKE_THIS = "NO_OBJECT_LIKE_THIS";
	case NONEXISTENT_PROPERTY= "NONEXISTENT_PROPERTY";


	/**
	 * @throws Exception
	 */
	public function throw(?string $message = N, ?string $description = N, ?\Throwable $previous = N, ?int $flags = N, ?array $additionalInfo = N): void
	{
		throw new Exception($this, $message, $description, $previous, $flags, $additionalInfo);
	}


}