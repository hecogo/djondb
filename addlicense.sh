#!/bin/sh

for i in *.cpp # or whatever other pattern...
do
	if ! grep -q /home/cross/workspace/djondb/template.txt $i
	then
		cat /home/cross/workspace/djondb/template.txt $i >$i.new && mv $i.new $i
	fi
done
