#!/bin/sh

read -p "Letra: " c

case $c in
#  a) echo "carater a";;
  a*) echo "carater a no inicio";;
  *a) echo "carater a no fim";;
  *) echo "outro carater"
esac
