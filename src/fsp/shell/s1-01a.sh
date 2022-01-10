#!/bin/sh

echo "Segundo shellscript"
echo 'narg ($#) = ' $#
for i in $@
do
  echo 'arg = ' $i
done
