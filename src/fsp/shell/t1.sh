#!/bin/sh

file=$1
max=$2
p=0

if [ $# -eq 2 ]
 then
  for v in $(cat $file)
  do
    if [ $v -gt 0 ] && [ $v -le $max ]; then
      p=$(($p + 1 ))
    fi
  done
  echo "Positivos = $p"
 else
  >&2 echo "Error nos parametros"
fi
