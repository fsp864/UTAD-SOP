#!/bin/sh

read -p "Valor para A: " A
read -p "Valor para B: " B

if [ $A -lt $B ]
 then 
  echo "A ($A) menor que B ($B)"
 else
  if [ $A -eq $B ]
   then
    echo "A ($A) igual a B ($B)"
   else
    echo "A ($A) maior a B ($B)"
  fi
fi
