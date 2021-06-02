#!/bin/bash
if [ -z "$1" ]; then
	echo "No input"
	exit 1
fi
BIN=./push_swap
C_BIN=./checker_Mac
if [ "$(uname)" = "Linux" ]; then
	C_BIN=./checker
	if [ ! -f "$C_BIN" ]; then
		make
		rm push_swap
	fi
fi
make debug >/dev/null
./push_swap -r "$1" > tmp
./$C_BIN $(cat .randstack) < tmp
rm .randstack tmp
