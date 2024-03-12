<?php


enum RequestClassResolverError: string
{


	case CLASS_NOT_EXISTS = "CLASS_NOT_EXISTS";
	case CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT= "CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT";


	/**
	 * @throws \RequestClassResolverException
	 */
	public function throw(?string $message = N)
	{
		throw new RequestClassResolverException($this, $message);
	}


}