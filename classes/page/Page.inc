<?php


namespace page;


abstract class Page extends \iw\page\driver\Page
{


	protected \APICall $api;


	/**
	 * @throws \iw\service\locator\Exception
	 */
	public function __construct(array $uriMatches, \iw\dom\Document $dom)
	{
		parent::__construct($uriMatches, $dom);
		$this->api = \World::_serviceLocator()->getService(svcAPI);
	}


}