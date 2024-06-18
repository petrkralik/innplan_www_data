<?php


class LocalAuthVerification extends \iw\page\html\auth\CredentialsVerification
{


	#[\Override] function verify(\iw\page\html\auth\Credentials $credentials): ?\iw\page\html\auth\UserInfo
	{
		if($credentials->getUsername()== "xxx" && $credentials->getPassword()== "xxx")
			return new \iw\page\html\auth\UserInfo(
				"xxx",
				1,
				"Test User"
			);

		return N;
	}


}