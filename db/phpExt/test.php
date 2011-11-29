<?php

if (!extension_loaded('djonPhpExt')) {
  echo 'Library not loaded';
}
$c = new Connection("localhost");

$c->djon_insert('a', '{ name: 1 }');
echo '<p>Hello World</p>';

?>
