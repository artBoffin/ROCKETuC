#!/bin/bash

lf=$1

for p in h c
do
	for i in *.${p}
	do
		if [ -f $i ]
		then
			echo "Adding license header to file $i"
			mv $i $i.orig
			cat $lf > $i
			cat $i.orig >> $i
		fi
	done
done
