#!/bin/sh


shopt -s extglob

case "$1" in
  +([0-9])* )
     echo sao 1 ou mais digitos no inicio
esac
