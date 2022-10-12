#!/bin/sh

file="$1"
IFS='
'

sections=""
values=""

if [ $# -gt 0 ] && [ -f $file ]
 then
  for line in $(cat $file)
  do
    case $line in
      \[*\] )  #sections
        section=$line
        echo "Section: $section"
	sections="$sections $section";;
      *\=* )  #values
	item=$(echo $line | cut -f1 -d '=')
	value=$(echo $line | cut -f2 -d '=')
        echo "$item: $value"
	items="$items $item"
    esac
  done
  echo "Sections: $sections"
  echo "Items: $items"
 else
  1>&2 echo "ERROR: Missing file or flie do not existe"
fi
