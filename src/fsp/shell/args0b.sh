#!/bin/sh

zeors=0
positivos=0
negativos=0

for i in $*
do 
  if [ $i -eq "0" ]
   then 
    zeros=$(($zeros + 1)) 
  fi
  if [ $i -lt "0" ]
   then 
    negativos=$(($negativos + 1)) 
  fi
  if [ $i -gt "0" ]
   then 
    positivos=$(($positivos + 1)) 
  fi
done

echo "Numero de argumentos (de $#) a zero = $zeros negativos = $negativos positivos = $positivos"
