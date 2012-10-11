#!/bin/sh

sh update.sh

rm -rf php
mkdir php

swig2.0 -c++ -php -outdir php -o php/djonphpdriver.cpp driver.i

cd php

g++ -I/usr/include/php5 -I/usr/include/php5/main -I/usr/include/php5/TSRM -I/usr/include/php5/Zend -I/usr/include/php5/ext -I`pwd`/../ -I/usr/include/php5/ext/date/lib -fpic -c djonphpdriver.cpp -o djonphpdriver.o
g++ -shared djonphpdriver.o -o djonphpdriver.so

zipfile="djondb_phpext_`uname`_`uname -m`.zip"

zip $zipfile djonphpdriver.so djonwrapper.php
