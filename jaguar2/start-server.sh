#!/bin/sh

c="."
for i in Jaguar-console/dist/* ; do
##  j=?
  c="$c:$i"
done
for i in Jaguar-console/dist/lib/* ; do
##  j=?
  c="$c:$i"
done

echo $c
## -agentlib:jdwp=transport=dt_socket,address=9797,server=y,suspend=y
echo java -classpath c$ jaguarconsole.Launcher
java -classpath $c jaguarconsole.Launcher


