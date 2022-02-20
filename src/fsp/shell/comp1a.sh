#!/bin/sh

read -p "Valor para A: " A
read -p "Valor para B: " B

if test $A -gt $B
 then echo "A ($A) maior que B ($B)"
 else echo "A ($A) menor ou igual a B ($B)"
fi
