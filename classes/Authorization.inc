<?php


class Authorization extends World {


	function getToken() {
		if($this-> needAuthorization()) {
			$sessionId= session_id();
			$username= $this-> cfg["api"]["username"];
			$password= $this-> cfg["api"]["password"];
			$a= new \iw\APICall();
			$a-> get("https://auth.westa.cz/token/?sessionId=$sessionId&username=$username&password=$password");
			if($a-> statusCode== \iw\HttpStatusCode::OK)
				$this-> saveToken($a-> response-> body);
		}
	}


	private function saveToken(stdClass $data): void {
		$_SESSION["iw"]["auth"]= [
			"userId"=>		$data-> userId,
			"token"=>		$data-> token,
			"validUntil"=>	$data-> validUntil
		];
	}


	private function needAuthorization(): bool {

		return !$this-> hasValidToken();
	}


	private function tokenExists(): bool {

		return isset($_SESSION["iw"]["auth"]);
	}


	private function hasValidToken(): bool {

		return ($_SESSION["iw"]["auth"]["validUntil"] ?? 0)> date("U");
	}






}