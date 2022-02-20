#!/bin/sh

read -p "Letra: " char

case $char in
  [aeiouAEIOU])
    echo "carater $char é uma vogal";;
  [a-zA-Z])
    echo "carater $char é consoante";; #aeuio excluidos devido ao 1º padrao
  [0-9])
    echo "carater $char é digito decimal";;
  [\+\-\/\*])
    echo "Operador";;
  *)
    echo "carater $char nao e' uma letra ou digito decimal ou operador"
esac
