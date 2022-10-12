#!/bin/sh

file=$1
IFS='
'
sections=""

if [ $# -gt 0 ] && [ -f $file ]
 then
  for line in $(cat $file) 
  do
    case $line in
      \[*\] )
        section=$line
	echo "Section = $section"
	sections="$sections $section";;
       *\=* )
	item=$(echo $line | cut -d"=" -f1)
	value=$(echo $line | cut -d"=" -f2)
	echo "Item = $item value = $value"
	items="$items $item"
    esac
  done
  echo "Sections = $sections"
  echo "Items = $items"
 else
  1>&2 echo "ERROR: Missing file or file not readable"
fi
