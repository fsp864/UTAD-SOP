#!/bin/sh

read -p "Valor para a: " a
read -p "Valor para b: " b
read -p "Valor para c: " c

if [ ( $a -eq $b ) -a ( $b -eq $c ) ]
 then	 
  echo "a ($a) b ($b) e c ($c) sao iguais"
 else
  echo "a ($a) b ($b) e c ($c) sao diferentes"
fi
