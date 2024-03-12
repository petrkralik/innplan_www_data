<?php


class CustomException extends \iw\Exception
{


	public mixed $error;


	function __construct($error, ?string $message, ?Throwable $previous= N, ?int $flags= N, ?array $additionalInfo= N)
	{
		$this->error = $error;
		parent::__construct($error->value, $message, N, $previous, $flags, $additionalInfo);
	}


}