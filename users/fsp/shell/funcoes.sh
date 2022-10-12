#!/bin/sh

#As funcoes devem ser descritas antes de serem utilizada
Separador()
{
  echo "-------------------------------------------"
}

soma()
{
  total=0
  for i in $*
  do
    total=$(($total + $i))
  done

  echo $total
}

#echo corpo de funcoes.sh
