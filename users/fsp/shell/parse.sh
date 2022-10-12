#!/bin/sh

file=$1

sections=""
items=""

IFS='
'

if [ $# -gt 0 ] && [ -f $lile ]
 then	
  for line in $(cat $file)
  do
    case $line in
      \[*\] )
	section=$(echo $line | cut -d'[' -f2 | cut -d']' -f1)
        sections="$sections $section"
        echo "Section = $section";;
      *=* )
	item=$(echo $line | cut -d= -f1)
	value=$(echo $line | cut -d= -f2)
        echo "Item $item = $value"
        items="$items $item"
    esac		  
  done
  echo "Sections = $sections"
  echo "Items = $items"
 else
  1>&2 echo "ERROR: File missing or not readable"
fi
