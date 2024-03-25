<?php


enum RequestClassResolverError: string
{


	/**
	 * This case occurs when a class does not exist in the application.
	 */
	case CLASS_NOT_EXISTS = "CLASS_NOT_EXISTS";

	/**
	 * This case is triggered when a class is not a successor (child) of the required parent class.
	 */
	case CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT = "CLASS_IS_NOT_SUCCESSOR_OF_REQUIRED_PARENT";


	/**
	 * @throws \RequestClassResolverException
	 */
	public function throw(?string $message = N)
	{
		throw new RequestClassResolverException($this, $message);
	}


}