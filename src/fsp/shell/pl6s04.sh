#!/bin/sh

ordem=1

for argumento in $*
do
  echo "argumento $ordem = $argumento"
  ordem=$(( ordem + 1 ))
done
