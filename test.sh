#!/bin/zsh
make
STEPS="5"
#step=(1 3 5 10 100)
step=(1 3 5 10 49 51 100)
RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[1;33m"
END="\e[0m"
for i in "${step[@]}"
do
	x=1
	echo "--------- input $i ----------"
	while [ $x -le $STEPS ]
	do
		ruby -e "puts (0..$i - 1).to_a.shuffle.join(' ')" > .args
		./push_swap $(cat .args) > .instr
		RES_N="$(cat .instr | wc | awk '{print $1}')" 
		echo -n "\tn of instr: $RES_N "
		RES_OK=$(./checker $(cat .args) <.instr)
		if [ $RES_OK = "OK" ]; then
			echo -e -n "${GREEN}[$RES_OK]"
		else
			echo -e -n "${RED}[$RES_OK]"
		fi
		echo -ne "${END}"
		if [ "$RES_N" -gt "700" ]; then
			echo -e "${YELLOW} [KO]${END}"
		else
			echo -e "${GREEN} [OK]${END}"
		fi
		x=$(( $x + 1 ))
	done
	echo "-----------------------------"
done
x=1
echo "--------- input 500 ----------"
while [ $x -le $STEPS ]
do
	ruby -e "puts (0..499).to_a.shuffle.join(' ')" > .args
	./push_swap $(cat .args) > .instr
	RES_N="$(cat .instr | wc | awk '{print $1}')" 
	echo -n "\tn of instr: $RES_N "
	RES_OK=$(./checker $(cat .args) <.instr)
	if [ $RES_OK = "OK" ]; then
		echo -e -n "${GREEN}[$RES_OK]"
	else
		echo -e -n "${RED}[$RES_OK]"
	fi
	echo -ne "${END}"
	if [ "$RES_N" -gt "5500" ]; then
		echo -e "${YELLOW} [KO]${END}"
	else
		echo -e "${GREEN} [OK]${END}"
	fi
	x=$(( $x + 1 ))
done

rm .instr .args
