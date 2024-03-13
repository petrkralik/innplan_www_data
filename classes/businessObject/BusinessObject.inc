<?php


namespace businessObject;


abstract class BusinessObject extends \World
{


	abstract function loadData(): bool;


}