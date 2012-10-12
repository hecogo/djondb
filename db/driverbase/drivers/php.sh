#!/bin/sh

sh update.sh

rm -rf php
mkdir php

swig2.0 -c++ -php -outdir php -o php/djonphpdriver.cpp driver.i

cp config.m4 php
cd php

phpize

./configure --enable-djonPhpExt
make


zipfile="djondb_phpext_`uname`_`uname -m`.zip"

zip $zipfile test.php modules/djonPhpExt.so djonwrapper.php
