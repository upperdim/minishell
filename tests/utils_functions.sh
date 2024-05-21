#! /bin/bash


RM="rm -rf"
# COLORS
BOLD_RED="\033[1;31m"
BOLD_GREEN="\033[1;32m"
BOLD_YELLOW="\033[1;33m"
ITALIC_YELLOW="\033[3;33m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
GREEN="\033[0;32m"
CYAN="\033[34m"
DEFAULT="\033[0m"

function prepare_logs_dir
{
	if [[ ! -d "tests/logs" ]]; then
		mkdir -p tests/logs
	fi
};

function check_norminette
{
	normerror=$(norminette | grep -E "Error:|Error!")
	if [ -n "$normerror" ]; then
		echo -e "$BOLD_RED Norminette error(s) detected, please fix it/them before running the pushing to vogsphere.$DEFAULT"
		echo -e $RED && norminette | grep -E "Error:|Error!" && echo -e $DEFAULT
	fi
};

function feedback
{
	failed=$(grep "Failed" tests/logs/result_parser.log)
	if [ -z "$failed" ]; then
		echo -e "$BOLD_GREEN All tests passed successfully.$DEFAULT"
		return
	fi
	echo -e "$BOLD_RED 1 or more test failed:$DEFAULT"
	(echo -ne "$RED"
	grep "Failed" tests/logs/result_parser.log
	echo -ne "$DEFAULT") | awk '{print "\t", $0}'
	echo -e "$CYAN Check Logs for more information$DEFAULT"
};


function run_valgrind
{
	LEAKS=$(valgrind --leak-check=full ./a.out 2>&1 | grep "ERROR SUMMARY:" | awk '{print $4}')

	rm -rf tests/logs/valgrind_$1_$2.log
	if [[ $LEAKS -ne 0 ]]; then
		valgrind --leak-check=full ./a.out 2> tests/logs/valgrind_$1_$2.log
		echo -e "$BOLD_RED Memory leaks detected in test $1 $2$DEFAULT"
		echo -e "$ITALIC_YELLOW Check tests/logs/valgrind_$1_$2.log for more information$DEFAULT"
		echo -e "\t\tFailed leak test in $1 $2" >> tests/logs/result_parser.log
		echo -e "\tCheck tests/logs/valgrind_$1_$2.log for more information" >> tests/logs/result_parser.log
	else
		echo -e "Leak test in $1 $2: PASS" >> tests/logs/result_parser.log
	fi
};
