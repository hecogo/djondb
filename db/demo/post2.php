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
		$c = new Connection();
		$_SESSION['connection'] = $c;

	}

		$c->connect("localhost");
//	$guid = uniqid();

	$data = $_POST['data'];

	$text = json_encode($data);

	$c->insert('djonlistdb', 'test.demo', $text);
}
print 'done';
?>
