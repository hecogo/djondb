<?php

if (!extension_loaded('djonPhpExt')) {
	if (strtoupper(substr(PHP_OS, 0, 3)) === 'WIN') {
		dl('djonPhpExt.dll');
	} else {
		dl('djonPhpExt.so');
	}
}

if (!extension_loaded('djonPhpExt')) {
	echo "Cannot load extension";
} else {
	$c = new Connection();

	$c->djon_connect("localhost");

	$type = $_GET['type'];

	$filter = '{ type: "'.$type.'"}';

	$jsonResult = $c->djon_findByFilter('djonlistdb', 'test.demo', $filter);

	print $jsonResult;
}
?>
