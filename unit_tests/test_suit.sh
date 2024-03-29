#! /bin/bash

RM="rm -rf"
CC=cc
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"
RED="\x1b[0;31m"
DEFAULT="\x1b[0m"
if [ -n "$(norminette | grep -E "Error:|Error!")" ]; then
	echo -e "\x1b[1;31mNorminette error(s) detected, please fix it/them before running the pushing to vogsphere.\x1b[0m"
	echo -e $RED && norminette | grep -E "Error:|Error!" && echo -e $DEFAULT
fi
make test
./test
$CC $CFLAGS unit_tests/test_parser.c
mkdir -p logs
if [ -n "$NEW_LOGS" ]; then
	$RM logs/*
	unset NEW_LOGS
fi
echo -e "====\t$(date +%d\ %b\ %Y\ @\ %T)\t====" >> logs/result_parser.log
./a.out >> logs/result_parser.log
echo -e "====\t\tEND of the log\t\t====" >> logs/result_parser.log
$RM a.out