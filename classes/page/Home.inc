<?php


namespace page;



class Home extends Page2Columns
{


	#[\Override] function getContentMain(): ?\iw\dom\Element
	{
		return $this->doc->h1(N, "Home");
	}


}