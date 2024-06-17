<?php
include ROOT_DATA. "/_shared/program/globalEnvironmentSettings.inc";
include ROOT_DATA. "/www/config.inc";

// Class autoloader definition
iw\Autoloader::_addPath(ROOT_DATA. "/www/classes");
iw\Autoloader::_addPath(ROOT_DATA. "/_shared/program/classes");
//iw\Autoloader::_addPath(ROOT_DATA. "/_shared/3rdParty/PHPMailer/src");

