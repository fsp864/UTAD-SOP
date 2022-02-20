#!/bin/sh

resvere=''

for i in $*
do
  reverse="$i $reverse"
done

echo $reverse
