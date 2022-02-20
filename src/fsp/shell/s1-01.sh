#!/bin/sh

echo "$0: ola mundo"
echo '$1=' $1
echo '$2=' $2
echo 'narg ($#) = ' $#
echo 'args ($*) = ' $*
echo 'args ($@) = ' $@
sh s1-01a.sh "$@"
sh s1-01a.sh "$*"
