#!/bin/sh

rm libs/*
find . -iwholename */lib*.so -exec cp -f {} libs \;
find . -iwholename */lib*.so.1* -exec cp -f {} libs \;
