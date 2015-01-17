#!/bin/bash

# run trackgen on all files, generate result to "generated"
# path to trackgen is expected as first parameter, e.g. ~/torcs_bin/bin/trackgen

[ -z "$1" ] && exit 1
[ ! -f "$1" ] && exit 1
pwd=`pwd`

for f in `find $pwd/source -name *.xml`; do
	path=${f%/*};
	name=${path##*/};
	categorypath=${path%/*}
	category=${categorypath##*/}
	genpath=${path/source/generated}
#   Generate "sources"
#	$1 -c $category -n $name -i $path -o $path -a

#   Generate "generated"
	$1 -c $category -n $name -i $path -o $genpath -a
done


