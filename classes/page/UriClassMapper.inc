<?php


namespace page;


class UriClassMapper extends \iw\page\driver\UriClassMapper
{


	public function defaultPageClassName(): string
	{
		return "\page\Home";
	}


	public function getMap(): array
	{
		return [
			"/\/project\/list\/?/i" => "\page\ProjectList",
			"/\/project\/state\/list\/?/i" => "\page\ProjectStateList",
			"/\/project\/(\d+)\/detail\/?/i" => "\page\ProjectDetail",
			"/\/client\/list\/?/i" => "\page\ClientList",
			"/\/resource\/list\/?/i" => "\page\ResourceList",
			"/\/project\/role\/list\/?/i" => "\page\ProjectRoleList",
			"/\/workType\/list\/?/i" => "\page\WorkTypeList",
			"/\/workType\/new\/(save)\/?/i" => "\page\WorkTypeNew",
			"/\/workType\/(new)\/?/i" => "\page\WorkTypeNew",
		];
	}


}