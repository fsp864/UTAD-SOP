#!/bin/sh

file=$1
count=0


#IFS='
#'
IFS=\

for linha in $(cat $file)
do
  case $linha in
    \#*) count=$(($count + 1))
         echo $linha;;
  esac
done

echo $count
