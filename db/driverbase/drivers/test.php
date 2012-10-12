<?php

include("djonwrapper.php");

$c = ConnectionManager::getConnection("localhost");
$c->open();

$guid = uniqid();
$json = "{ _id: '$guid', name: 'Juan', lastName: 'Cross'}";

$c->insert('phpdb', 'a', $json);
echo '<p>Inserted</p>';

echo '<p>Finding</p>';
$res = $c->find('phpdb', 'a', '$"name" == "Juan"');

for ($x = 0; $x < $res->size(); $x++) {
	echo $res->get($x)->toChar();
}

?>
