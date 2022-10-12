#!/bin/sh

file=$1
numero=1
IFS='
'

linhas=$(cat $file)

for linha in $linhas
do
  echo "Linha $numero:$linha"
  numero=$(($numero + 1))
done
