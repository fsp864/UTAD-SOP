#!/bin/sh

. ./funcoes.sh          #Incluir o script das funcoes
#source ./funcoes.sh     #tambem funciona no bash

#Corpo do script
Separador
somatorio=$(soma $*)
echo "soma de $* = $somatorio"
Separador
echo "soma de 1 2 3 = $(soma 1 2 3)"
Separador 

#exit 11
#echo depois de exit
