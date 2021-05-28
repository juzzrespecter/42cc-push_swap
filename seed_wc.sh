#!/bin/bash
make bonus
step=(1 3 5 10 20 50 100 200 500 1000)
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
