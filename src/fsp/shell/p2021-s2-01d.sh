#!/bin/sh

read -p "Valor para A: " A
read -p "Valor para B: " B

if [ $A -lt $B ]
 then 
  echo "A ($A) menor que B ($B)"
 elif [ $A -eq $B ]
   then
    echo "A ($A) igual a B ($B)"
   elif [$A -gt $B ]
     echo "A ($A) maior a B ($B)"
fi
