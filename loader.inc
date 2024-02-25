<?php
const ROOT_DATA= "/var/www_data/westa.cz/innplan";

include "environmentSettings.inc";
include ROOT_DATA. "/_shared/program/standardErrorHandler.inc";

$w= new WorldBuilder();
$w-> buildTheWorld();
