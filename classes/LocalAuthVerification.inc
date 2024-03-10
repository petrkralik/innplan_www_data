<?php


class LocalAuthVerification extends \iw\auth\CredentialsVerification
{


	#[\Override] function verify(\iw\auth\Credentials $credentials): ?\iw\auth\UserInfo
	{
		if($credentials->getUsername()== "xxx" && $credentials->getPassword()== "xxx")
			return new \iw\auth\UserInfo(
				"xxx",
				1,
				"Test User"
			);

		return N;
	}


}