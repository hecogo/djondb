<?php

// session_start(); // start up your PHP session! 

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

	$c->connect("localhost");

	$guid = uniqid();
	$json = "{ _id: '$guid', name: 'Juan', lastName: 'Cross'}";

	$c->insert('phpdb', 'a', $json);
	echo '<p>Inserted</p>';

	echo '<p>Finding</p>';
	$c->findByFilter('phpdb', 'a', '$\'name\' == \'Juan\'');

}
?>
