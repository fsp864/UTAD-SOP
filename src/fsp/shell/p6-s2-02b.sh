#!/bin/sh

read -p "Valor para A: " A
read -p "Valor para B: " B

if [ $A -gt $B ]
 then
  echo "A ($A) maior que B ($B)"
 else
  if [ $A -lt $B ]
   then
    echo "A ($A) menor que ($B)"
   else
    echo "A ($A) igual a B ($B)"
  fi
fi
