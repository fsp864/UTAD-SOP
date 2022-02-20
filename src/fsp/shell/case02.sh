#!/bin/sh

file=$1                                    #ficheiro igual ao primeiro argumento

ERRO="$0: erro - ficheiro nao existe ou nao foi indicado"
USAGE="Instrucao: $0 \"ficheiro\""
                                       #verificar se foi indicado um argumento e
if [ $# -gt 0 ] && [ -f $file ]; then             #se existe ficheiro (man test)
  echo "ficheiro: $file"                                        #apresentar menu
  echo "m - mostrar conteudo"
  echo "p - contar palavras"
  echo "l - contar linhas"
  echo -n "Opcao: "

  read opcao                                                   #leitura da opcao

  case $opcao in                                               #selecionar opcoo
    m) cat $file;;                              #apresentar conteudo do ficheiro
                                                     #obter o numero de palavras
    p) echo "O ficheiro tem $(cat $file | wc -w) palavras";;
	                                               #obter o numero de linhas
    l) lines=$(cat $file | wc -l)
       echo "O ficheiro tem $lines linhas";;
			                                     #opcao para o resto
    *) echo Opcao invalida;;                               #;; nao e' necessario
  esac
 else
  echo $ERRO                                                   #mensagem de erro
  echo $USAGE                                                 #mensagem de ajuda
fi
