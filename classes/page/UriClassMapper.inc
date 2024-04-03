<?php


namespace page;


class UriClassMapper extends \page\driver\UriClassMapper
{


	public function defaultPageClassName(): string
	{
		return "\page\Home";
	}


	public function getMap(): array
	{
		return [
			"/\/project\/list\/?/i"          => "\page\ProjectList",
			"/\/project\/state\/list\/?/i"   => "\page\ProjectStateList",
			"/\/project\/(\d+)\/detail\/?/i" => "\page\ProjectDetail",
			"/\/client\/list\/?/i"           => "\page\ClientList",
		];
	}


}