#!/bin/bash
if [ -z "$1" ]; then
	echo "No input"
	exit 1
fi
BIN=./push_swap
C_BIN=./checker
if [ ! -f "$C_BIN" ]; then
	make
	rm push_swap
fi
if [ ! -f "$BIN" ]; then
	make bonus
fi
./push_swap -r "$1" > tmp
./checker_Mac $(cat .randstack) < tmp
rm .randstack tmp
