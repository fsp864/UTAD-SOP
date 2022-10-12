#!/bin/sh

valor=1     #nao ser 0 na primeira interacao
soma=0

#while test $valor -ne 0
while [ "$valor" -ne 0 ]
do
  read -p "Indique um valor (0 para finalizar): " valor
  soma=$(($soma + $valor))
done

echo "Soma dos valores introduzidos = $soma"
