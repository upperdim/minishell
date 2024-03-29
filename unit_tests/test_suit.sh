#! /bin/bash
source unit_tests/utils_functions.sh

CC=cc
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"

check_norminette
prepare_logs_dir
make test
./test
$CC $CFLAGS unit_tests/test_parser.c
echo -e "====\t\t$(date +%d\ %b\ %Y\ @\ %T)\t\t====" >> logs/result_parser.log
./a.out >> logs/result_parser.log
echo -e "====\t\t\tEND of the log\t\t\t====" >> logs/result_parser.log
$RM a.out