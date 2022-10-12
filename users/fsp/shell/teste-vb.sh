#!/bin/sh

c=0
nc=0

for item in $(ls); do
  if echo $item | grep .txt; then
    c=$(( $c + 1 ));
   else
    nc=$(( $nc + 1 ));
  fi
done

echo Encontrados $c ficheiros texto
echo Encontrados $nc ficheiros de outro tipo
