#!/bin/sh
for i in *; do
a=`grep -L "$i" index.htm`
 if [ -n "$a" ]; then
 echo $i
fi
done
