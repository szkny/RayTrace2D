#! /bin/bash

SS=EffMap2d_
OUTPUT=animation
N=1
for i in $(seq -w 1 1 9)
	do if test -e "${SS}${N}0mm.eps"; then
		echo "${SS}${N}0mm.eps -> ${SS}${i}0mm.png"
		convert ${SS}${N}0mm.eps ${SS}${i}0mm.png
		N=$((++N))
	fi
done

