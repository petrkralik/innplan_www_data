<?php


namespace page\driver;


class Exception extends \iw\Exception
{


	public readonly Error $error;


	public function __construct(Error $error, ?string $message = N, ?string $description = N, ?\Throwable $previous = N, ?int $flags = N, ?array $additionalInfo = N)
	{
		$this->error= $error;
		parent::__construct($error->value, $message, $description, $previous, $flags, $additionalInfo);
	}


}