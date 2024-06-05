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

			// Work Type
			"/\/workType\/list\/?/i" => "\page\WorkType\WorkTypeList",
			"/\/workType\/new\/(save)\/?/i" => "\page\WorkType\WorkTypeNew",
			"/\/workType\/(new)\/?/i" => "\page\WorkType\WOrkTypeNew",
			"/\/workType\/(\d+)\/?$/i" => "\page\WorkType\WorkTypeDetail",
			"/\/workType\/(\d+)\/edit\/(save)\/?/i" => "\page\WorkType\WorkTypeEdit",
			"/\/workType\/(\d+)\/edit\/?/i" => "\page\WorkType\WorkTypeEdit",
			"/\/workType\/(\d+)\/delete\/(processing)\/?/i" => "\page\WorkType\WorkTypeDelete",
			"/\/workType\/(\d+)\/delete\/?/i" => "\page\WorkType\WorkTypeDelete",
		];
	}


}