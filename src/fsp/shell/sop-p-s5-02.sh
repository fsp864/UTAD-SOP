#!/bin/sh
# Ficheiro : sop-p-s5-02.sh

# funcoes ######################################################################
ApresentarTexto()                                               # nome da funcao
{
  texto=$1                                # $1 representa 1º argumento da funcao
  char=$2                                 # $2 representa 2º argumento da funcao
  colunas=$3

  total=$(expr $colunas - $(expr length "$texto"))

  juntar=''
  echo -n $texto
  while [ $total -gt 0 ]
  do
    juntar="$juntar$char"                                     # concatenar texto 
    total=$(expr $total - 1)
  done
  echo $juntar                        # apresentar caracter ate' ao fim da linha 
}

# parte principal ##############################################################
#colunas=80

while [ "$texto" != "sair" ]
do
  echo -n "Introduza texto: "
  read texto                                                         # ler texto
  ApresentarTexto "$texto" '#' 80
  ApresentarTexto "$texto" '-' 100
done
