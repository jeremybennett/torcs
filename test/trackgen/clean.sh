#!/bin/bash

#delete generated ac files from "generated"

pwd=`pwd`

for f in `find $pwd/generated -name *.ac`; do
	rm $f;
done