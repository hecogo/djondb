<?php

if (!extension_loaded('djonPhpExt')) {
  echo 'Library not loaded';
}
session_start(); // start up your PHP session! 

if (isset($_SESSION['connection'])) {
   $c = $_SESSION['connection'];
} else {
  echo '<p>Starting new connection</p>';
  $c = new Connection("localhost");
  $_SESSION['connection'] = $c;

}

$guid = uniqid();
$json = "{ _id: '1', name: 'Juan', lastName: 'Cross'}";

echo $json;

$c->djon_insert('a', $json);


echo '<p>Inserted</p>';

?>
