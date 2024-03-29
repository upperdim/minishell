#! /bin/bash

RED="\x1b[0;31m"
DEFAULT="\x1b[0m"
RM="rm -rf"

function prepare_logs_dir
{
	if [ ! -d "logs" ]; then
		mkdir -p logs
	fi
	if [ -n "$NEW_LOGS" ]; then
		$RM logs/*
	fi
};

function check_norminette
{
	if [ -n "$(norminette | grep -E "Error:|Error!")" ]; then
		echo -e "\x1b[1;31mNorminette error(s) detected, please fix it/them before running the pushing to vogsphere.\x1b[0m"
		echo -e $RED && norminette | grep -E "Error:|Error!" && echo -e $DEFAULT
	fi
};
