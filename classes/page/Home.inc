<?php


namespace page;



class Home extends Page2Columns
{


	#[\Override] function getContentMain(): ?\iw\dom\Element
	{
		return $this->doc->{\iw\html::E_H1}(N, "Home");
	}


}