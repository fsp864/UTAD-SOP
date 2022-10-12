#!/bin/sh

read -p "Valor de A = " a
read -p "Valor de B = " b
read -p "Valor de operador = " op

case $op in
  +)
    echo "$a + $b = $(( $a + $b))";;
  -)
    echo "$a - $b = $(( $a - $b))";;
  [\*x])
    echo "$a * $b = $(( $a * $b))";;
  [\/:])
    if [ $b -ne 0 ]
     then
      echo "$a / $b (inteira)= $(( $a / $b))"
      echo "$a / $b (resto)= $(( $a % $b))"
     else
      echo "Divisao por 0"
    fi;;
  *)
    echo "Operacao invalida" 
esac
