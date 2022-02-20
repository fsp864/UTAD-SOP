#!/bin/sh

read -p "Valor para A: " A
read -p "Valor para B: " B

if [ $A -lt $B ]
 then 
  echo "A ($A) menor que B ($B)"
 else
  echo "A ($A) maior ou igual a B ($B)"
fi
