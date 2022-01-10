#!/bin/sh

#for i in $(seq 0 100)
for i in {0..100}
do
echo -e -n "\r$i%"	
#  echo -n "\b\b\b$i%"	
#  echo -n "\f$i%"	
  sleep 1
done
echo
