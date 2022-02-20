#!/bin/sh

n="0"

for i in $*
do 
  if [ $i -eq "0" ]
   then 
#    n=$(($n + 1)) # incrementar n
#    n=$[$n + 1] # incrementar n so no bash
    n=$(expr $n + 1) # incrementar n
  fi
done

echo "Numero de argumentos (de $#) a zero = $n"
