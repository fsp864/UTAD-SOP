#!/bin/sh

echo "Isto é um shellscript com o nome $0" #escrever o nome do shellscript
echo 'Isto é um shellscript com o nome $0' #escrever o nome do shellscript
echo "Argumento 1 = $1"
echo "Argumento 2 = $2"
echo "n arg: $#"
echo 'Argumentos ($*) =' $*
echo 'Argumentos ($@) =' $@
