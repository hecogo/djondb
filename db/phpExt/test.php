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
   $c = NULL;
	if (isset($_SESSION['connection'])) {
		$c = $_SESSION['connection'];
	}
	if (is_null($c)) {
		echo '<p>Starting new connection</p>';
		$c = new Connection();
		$_SESSION['connection'] = $c;

	}

	$c->djon_connect("localhost");
	$guid = uniqid();
	$json = "{ _id: '$guid', name: 'Juan', lastName: 'Cross'}";

	$c->djon_insert('phpdb', 'a', $json);

	echo '<p>Inserted</p>';
}
?>
