g++ -shared -Wl,-soname,libtestjni.so -static -lc -I/usr/lib/jvm/java-6-openjdk/include -c test.cpp Test.cpp
g++ -o libtestjni.so -shared -Wl,-soname,libtestjni.so -static -lc -I/usr/lib/jvm/java-6-openjdk/include test.o Test.o
