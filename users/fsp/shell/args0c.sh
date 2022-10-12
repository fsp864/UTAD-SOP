#!/bin/sh

zeors=0
positivos=0
negativos=0

for i in $*
do 
  if [ $i -eq "0" ]
   then 
    zeros=$(($zeros + 1)) 
  elif [ $i -lt "0" ]
   then 
    negativos=$(($negativos + 1)) 
   else
    positivos=$(($positivos + 1)) 
  fi
done

echo "Numero de argumentos (de $#) a zero = $zeros negativos = $negativos positivos = $positivos"
