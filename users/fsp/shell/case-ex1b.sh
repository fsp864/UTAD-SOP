#!/bin/sh

#read -p "Valor de A = " a
#read -p "Valor de B = " b
#read -p "Valor de operador = " op
a=$1
b=$2
op=$3

case $op in
  +)
    echo "$a + $b = $(( $a + $b))";;
  -)
    echo "$a - $b = $(( $a - $b))";;
  [\*x])
    echo "$a * $b = $(( $a * $b))";;
  [\/\:])
      echo "$a / $b = $(( $a / $b))";;
  ?)
    echo one char $op;;
  *)
    echo "Operacao invalida" 
esac
