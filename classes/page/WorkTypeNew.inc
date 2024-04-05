<?php


namespace page;


class WorkTypeNew extends Page2Columns
{


	function getContentMain(): ?\iw\dom\Element
	{
		return $this->dom->div(
			[
				\iw\html::A_CLASS=> "workTypeNew"
			],
			$this->dom->h1(N, "nový typ práce")
		);
	}


}