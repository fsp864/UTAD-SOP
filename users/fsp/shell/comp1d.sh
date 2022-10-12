#!/bin/sh

A=$1
B=$2

if [ $A -eq $B ]
 then
  echo "A ($A) igual a B($B)"
 else
  if [ $A -le $B ]
   then
    echo "A ($A) menor que B ($B)"
   else
    echo "A ($A) maior que B ($B)"
  fi
fi
