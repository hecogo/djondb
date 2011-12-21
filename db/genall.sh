cd util/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..


cd bson/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd cache/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd filesystem/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd db/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd command/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd network/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd driverbase/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd service/obj
../configure --enable-debug --prefix=/usr;make clean;make;sudo make install
cd ../..
cd daemon/obj
../configure --enable-debug --prefix=/usr;make clean;make
cd ../..

# php
cd phpExt
phpize
./configure --enable-djonPhpExt
make clean;
make
sudo make install
cd ..

cd shell;rm -rf obj;mkdir obj;cd obj
../configure; make clean;make
cd ../..

