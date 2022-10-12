#!/bin/sh

# funcoes ######################################################################
PrimeiraFuncao()                                                # nome da funcao
{
  echo "Dentro da funcao!!!"
  echo "Nome da funcao NAO E': $0"
  echo "Numero de argumentos passados para a funcao: $#"
  echo "Argumento 1 da funcao foi: $1"
  echo "Argumento 2 da funcao foi: $2"
  echo "Argumentos da funcao foram: $*"
  echo "Fim da funcao!!!" 
}

# parte principal ##############################################################
echo "Shellscript: invocando funcao..."
echo "Numero de argumentos passados para a script: $#"
#PrimeiraFuncao arg1 arg2 arg3 arg4 arg5
PrimeiraFuncao "$*"
