#! /bin/bash
source unit_tests/utils_functions.sh

CC=cc
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"
INCLUDES="-Iincludes -Ilib/libft/includes"
LIBRARIES="-Llib/libft -lft"

PARSER_FILES="src/parser/parser.c"

function run_parser_test_1
{
	for TEST_NUMBER in {1..3};
	do
	$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES unit_tests/test_parser.c -DTEST=$TEST_NUMBER
	./a.out >> logs/result_parser.log
	done
}

check_norminette
prepare_logs_dir
make test
./test
make -s lib/libft/libft.a
echo -e "====\t\t$(date +%d\ %b\ %Y\ @\ %T)\t\t====" > logs/result_parser.log
run_parser_test_1
echo -e "====\t\t\tEND of the log\t\t\t====" >> logs/result_parser.log
feedback
$RM a.out