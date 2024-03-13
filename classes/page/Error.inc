<?php


namespace page;


enum Error: string
{

	case TEMPLATE_ELEMENT_MISSING= "TEMPLATE_ELEMENT_MISSING";


	/**
	 * @throws \page\Exception
	 */
	function throw(?string $message): void
	{
		throw new Exception($this, $message);
	}


}