<?php


class RequestClassResolverException extends CustomException
{


	function __construct(RequestClassResolverError $error, string $message)
	{
		parent::__construct($error, $message);
	}


}