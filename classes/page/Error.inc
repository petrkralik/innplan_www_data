<?php


namespace page;


enum Error: string
{


	case GENERAL = "GENERAL";
	case TEMPLATE_ELEMENT_MISSING = "TEMPLATE_ELEMENT_MISSING";
	case API_READ_ERROR= "API_READ_ERROR";


	/**
	 * @throws \page\Exception
	 */
	public function throw(?string $message = N, ?string $description = N, ?\Throwable $previous = N, ?int $flags = N, ?array $additionalInfo = N): void
	{
		throw new Exception($this, $message, $description, $previous, $flags);
	}


}