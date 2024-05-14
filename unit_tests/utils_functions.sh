#! /bin/bash

RED="\x1b[0;31m"
DEFAULT="\x1b[0m"
RM="rm -rf"

function prepare_logs_dir
{
	if [[ ! -d "logs" ]]; then
		mkdir -p logs
	fi
};

function check_norminette
{
	normerror=$(norminette | grep -E "Error:|Error!")
	if [ -n "$normerror" ]; then
		echo -e "\x1b[1;31mNorminette error(s) detected, please fix it/them before running the pushing to vogsphere.\x1b[0m"
		echo -e $RED && norminette | grep -E "Error:|Error!" && echo -e $DEFAULT
	fi
};

function feedback
{
	failed=$(grep "Failed" logs/result_parser.log)
	if [ -z "$failed" ]; then
		echo -e "\x1b[1;32mAll tests passed successfully.\x1b[0m"
		return
	fi
	echo -e "\x1b[1;31m1 or more test failed:\x1b[0m"
	(echo -ne "\x1b[0;31m"
	grep "Failed" logs/result_parser.log
	echo -ne "\x1b[0m") | awk '{print "\t", $0}'
	echo -e "\x1b[34mCheck Logs for more information\x1b[0m"
};


function run_valgrind
{
LEAKS=$(valgrind --leak-check=full ./a.out 2>&1 | grep "ERROR SUMMARY:" | awk '{print $4}')

	if [[ $LEAKS -ne 0 ]]; then
		valgrind --leak-check=full ./a.out >> logs/result_parser.log
		echo -e "\x1b[1;31mMemory leaks detected in test $1 $2\x1b[0m"
	else
		echo -e "\x1b[1;32mNo memory leaks detected in test $1 $2\x1b[0m"
	fi
};
