#!/bin/sh

sh update.sh
swig2.0 -outdir java/java/src/djondb -o java/native/javadriver_wrap.cpp -c++ -java -package djondb driver.i

