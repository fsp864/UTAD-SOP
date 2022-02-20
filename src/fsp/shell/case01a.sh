#!/bin/sh

read -p "Letra: " char

case $char in
  [a-fA-F]*) echo "carater a ate' f" ;;
  [d-zD-Z]*) echo "carater d ate' z";;
  [0-9]*) echo "digito";;
  [\+\-\/\*]*) echo "operador";;
  *) echo "outro conjunto carater que nao a ate' z"
esac
