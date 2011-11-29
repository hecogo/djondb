<?php

if (!extension_loaded('djonPhpExt')) {
  echo 'Library not loaded';
}
$c = new Connection("a");

$c->djon_insert('a', 'a');
echo '<p>Hello World</p>';

?>
