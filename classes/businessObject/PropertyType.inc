<?php


namespace businessObject;


abstract class PropertyType
{


	public function __construct()
	{
	}


	/**
	 * @throws Exception
	 */
	public function set(mixed $value): void {
		Error::CLASS_MUST_IMPLEMENT_METHOD_SET-> throw("Class {$this::class} must implement method set().");
	}


	/**
	 * @throws Exception
	 */
	public function get(): mixed
	{
		Error::CLASS_MUST_IMPLEMENT_METHOD_GET-> throw("Class {$this::class} must implement method get().");
	}

}