#!/bin/sh

read -p "Valor de A = " a
read -p "Valor de B = " b
read -p "Valor de operador = " op

case $op in
  +)
    echo "$a + $b = $(( $a + $b))";;
  -)
    echo "$a - $b = $(( $a - $b))";;
  \*)
    echo "$a * $b = $(( $a * $b))";;
  \/)
    echo "$a / $b = $(( $a / $b))";;
  *)
    echo "Operacao invalida" 
esac
