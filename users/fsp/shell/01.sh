#!/bin/bash

zeros="0"

for i in $*
do
  if [ "$i" -eq "0" ]
   then
    zeros=$[ $zeros + 1 ]
  fi
done

echo "$zeros parametros sao zero"
