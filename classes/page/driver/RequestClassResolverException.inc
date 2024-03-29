<?php


namespace page\driver;


class RequestClassResolverException extends \iw\Exception
{


	public readonly RequestClassResolverError $error;


	public function __construct(RequestClassResolverError $error, ?string $message = N, ?string $description = N, ?\Throwable $previous = N, ?int $flags = N, ?array $additionalInfo = N)
	{
		$this->error= $error;
		parent::__construct($error->value, $message, $description, $previous, $flags, $additionalInfo);
	}


}