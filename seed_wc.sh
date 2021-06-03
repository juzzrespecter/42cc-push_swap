#!/bin/bash
make debug >/dev/null
step=(1 3 5 10 20 50 100 200 500 1000)
#step=(160 200 240 290 320 500)
#step=(151 152 153 154 250 251 252 498 499 500 501 502)
for i in "${step[@]}"
do
	x=1
	echo "--------- input $i ----------"
	while [ $x -le 5 ]
	do
		./push_swap -r $i | wc
		sleep 1
		x=$(( $x + 1 ))
	done
	echo "-----------------------------"
done
