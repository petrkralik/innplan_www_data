<?php


enum RequestClassResolverError: string
{


	case CLASS_NOT_EXISTS = "CLASS_NOT_EXISTS";


	/**
	 * @throws \RequestClassResolverException
	 */
	public function throw(?string $message = N)
	{
		throw new RequestClassResolverException($this, $message);
	}


}