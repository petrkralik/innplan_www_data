<?php


namespace page\driver;


abstract class UriClassMapper
{


	abstract public function defaultPageClassName(): string;
	abstract public function getMap(): array;



}