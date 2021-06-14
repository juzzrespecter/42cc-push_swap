#!/bin/zsh

# ------------------
step=(1 3 5 10 50 100)
RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[1;33m"
ORANGE="\x1b[255;165;0"
END="\x1b[0m"
# ------------------

# ------------------
STEPS="15"
m_steps=(10 20 50 100)
b_steps=(200 300 500)
bb_steps=(1000 1500)
# ------------------

make

# ======= small  tests ========

echo "--------- input 1 ----------"
x=1
while [ $x -le $STEPS ]
do
	ARGS="$(ruby -e "puts (0..0).to_a.shuffle.join(' ')")"
	RES_N="$(./push_swap $(echo $ARGS) | wc | awk '{print $1}')"
	echo -e -n "Number of instr: $RES_N "
	if [ "$RES_OK" = "OK" ]; then
		echo -e -n "${GREEN}[$RES_OK]"
	else
		echo -e -n "${GREEN} [OK]${END}"
	fi
	if [ "$RES_N" -ne 0 ]; then
		echo -e "${RED} [KO]${END}"
	else
		echo -e "${GREEN} [OK]${END}"
	fi
	x=$(( $x + 1 ))
done
echo "----------------------------"

echo "--------- input 3 ----------"
x=1
while [ $x -le $STEPS ]
do
	ARGS="$(ruby -e "puts (0..2).to_a.shuffle.join(' ')")"
	RES_N="$(./push_swap $(echo $ARGS) | wc | awk '{print $1}')"
	RES_OK=$(./push_swap $(echo $ARGS) | ./checker $(echo $ARGS))
	echo -e -n "Number of instr: $RES_N "
	if [ "$RES_OK" = "OK" ]; then
		echo -e -n "${GREEN}[$RES_OK]"
	else
		echo -e -n "${GREEN} [OK]${END}"
	fi
	if [ "$RES_N" -gt 2 ]; then
		echo -e "${RED} [KO]${END}"
	else
		echo -e "${GREEN} [OK]${END}"
	fi
	x=$(( $x + 1 ))
done
echo "----------------------------"

echo "--------- input 5 ----------"
x=1
while [ $x -le $STEPS ]
do
	ARGS="$(ruby -e "puts (0..4).to_a.shuffle.join(' ')")"
	RES_N="$(./push_swap $(echo $ARGS) | wc | awk '{print $1}')"
	RES_OK=$(./push_swap $(echo $ARGS) | ./checker $(echo $ARGS))
	echo -e -n "Number of instr: $RES_N "
	if [ "$RES_OK" = "OK" ]; then
		echo -e -n "${GREEN}[$RES_OK]"
	else
		echo -e -n "${GREEN}[OK]${END}"
	fi
	if [ "$RES_N" -gt 12 ]; then
		echo -e "${RED} [KO]${END}"
	else
		echo -e "${GREEN} [OK]${END}"
	fi
	x=$(( $x + 1 ))
done
echo "----------------------------"

# =============================


# ======= medium tests ========

for i in "${m_steps[@]}"
do
	x=1
	echo "--------- input $i ----------"
	while [ $x -le $STEPS ]
	do
		ARGS="$(ruby -e "puts (-$i..0 - 1).to_a.shuffle.join(' ')")"
		RES_N="$(./push_swap $(echo $ARGS) | wc | awk '{print $1}')"
		RES_OK=$(./push_swap $(echo $ARGS) | ./checker $(echo $ARGS))
		echo -e -n "Number of instr: $RES_N "
		if [ "$RES_OK" = "OK" ]; then
			echo -e -n "${GREEN}[$RES_OK]"
		else
			echo -e -n "${RED}[$RES_OK]"
		fi
		echo -n -e "${END}"
		if [ "$RES_N" -gt "700" ]; then
			if [ "$RES_N" -gt "1100" ]; then
				if [ "$RES_N" -gt "1500" ]; then
					echo -e "${RED} [KO]${END}"
				else
					echo -e "${ORANGE} [KO]${END}"
				fi
			else
				echo -e "${YELLOW} [KO]${END}"
			fi
		else
			echo -e "${GREEN} [OK]${END}"
		fi
		x=$(( $x + 1 ))
	done
	echo "-----------------------------"
done

# =============================


# ======== big tests ==========

for i in "${b_steps[@]}"
do
	x=1
	echo "--------- input $i ----------"
	while [ $x -le $STEPS ]
	do
		ARGS="$(ruby -e "puts (0..499).to_a.shuffle.join(' ')")"
		RES_N="$(./push_swap $(echo $ARGS) | wc | awk '{print $1}')"
		RES_OK=$(./push_swap $(echo $ARGS) | ./checker $(echo $ARGS))
		echo -n -e "Number of instr: $RES_N "
		if [ "$RES_OK" = "OK" ]; then
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
	echo "------------------------------"
done

# =============================
