<?php


namespace page\form;


class Form
{


	public readonly string $name;
	public readonly string $id;


	public function __construct(string $name, string $id)
	{
		$this->name = $name;
		$this->id = $id;
	}


}