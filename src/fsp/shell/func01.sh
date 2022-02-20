#!/bin/sh

#As funcoes devem ser descritas antes de serem utilizadas
Separador() 
{
  echo "-------------------------------------------"
}

#Corpo do script
Separador
read -p "Valor para a: " a
read -p "Valor para b: " b
Separador
echo "$a + $b = $(($a + $b))"
Separador
