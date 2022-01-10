#!/bin/sh

read -p "Valor para A: " A
read -p "Valor para B: " B

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
