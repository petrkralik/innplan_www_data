<?php


namespace page;


class WorkTypeEdit extends Page2Columns
{

	function getContentMain(): ?\iw\dom\Element
	{
		return $this->dom->div(N, "Edit");
	}


}