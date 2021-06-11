#!/bin/zsh
make
#step=(1 3 5 10 20 50 100 200 500 1000)
#step=(1 2 3 5 10 15 20 30 50 70 80 90 100 110)
#step=(160 200 240 290 320 500)
#step=(151 152 153 154 250 251 252 498 499 500 501 502)
step=(100 500)
RED="\e[31m"
GREEN="\e[32m"
END="\e[0m"
for i in "${step[@]}"
do
	x=1
	echo "--------- input $i ----------"
	while [ $x -le 100 ]
	do
		ruby -e "puts (0..$i - 1).to_a.shuffle.join(' ')" > .args
		./push_swap $(cat .args) > .instr
		echo -n "$(cat .instr | wc) "
		RES=$(./checker $(cat .args) <.instr)
		if [ $RES = "OK" ]; then
			echo -e "${GREEN}[$RES]"
		else
			echo -e "${RED}[$RES]"
		fi
		echo -ne "${END}"
		
		x=$(( $x + 1 ))
	done
	echo "-----------------------------"
done
rm .instr .args
