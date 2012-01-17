<?php

session_start(); // start up your PHP session! 
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

	$data = $_POST['data'];

	$text = json_encode($data);

	$c->djon_insert('list.classified', $text);
}
print '{ "result": "done"}';
?>
