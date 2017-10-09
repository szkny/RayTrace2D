#! /bin/bash
if type "date" > /dev/null 2>&1;then
	date
fi
SUFFIX1=eps
SUFFIX2=png
for f in *.${SUFFIX1};do
	echo "${f} -> ${f%.*}.${SUFFIX2}"
	convert ${f} ${f%.*}.${SUFFIX2}
done
rm *.${SUFFIX1}
if type "date" > /dev/null 2>&1;then
	date
fi
