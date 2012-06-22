#!/bin/sh

echo "<<<<<  Executing autoreconf  >>>>>"

autoreconf --install --force

rm -rf obj
mkdir obj
cd obj
../configure --prefix=/usr
make
make DESTDIR=`pwd` install
rm usr/bin/test*
rm -rf ../debian/usr
mv usr ../debian/

cd ..
sh debian.sh

scp djondb.deb crossleyjuan@d-jon.com:html/downloads/djondb.deb

