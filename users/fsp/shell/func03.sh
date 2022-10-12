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

#Corpo do script
Separador
somatorio=$(soma $*)
echo "soma de $* = $somatorio"
Separador
echo "soma de 1 2 3 = $(soma 1 2 3)"
Separador 
