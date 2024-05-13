#! /bin/bash
source unit_tests/utils_functions.sh

CC=cc
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"
INCLUDES="-Iincludes -Ilib/libft/includes -Iunit_tests/includes"
LIBRARIES="-Llib/libft -lft"
DEBUG="-g3"
if [[ "$1" == "d" || "$2" == "d" ]]; then
	CFLAGS="$CFLAGS $DEBUG"
	echo -e "\x1b[1;33mDebug mode enabled\x1b[0m"
fi
if [[ "$(uname)" == "Linux" ]]; then
	MANUALLY_ADDED_LIBFT="lib/libft/libft.a"
	VALGRIND="valgrind --leak-check=full ./a.out"
fi


PARSER_FILES="src/parser/parser.c src/parser/ft_create_tokens.c src/parser/create_tokens_utilities.c"

function run_parser_test_1
{
	for TEST_NUMBER in {1..3};
	do
	$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES unit_tests/test_parser.c -DTEST=$TEST_NUMBER $MANUALLY_ADDED_LIBFT
	$VALGRIND
	./a.out >> logs/result_parser.log
	done
}

function run_parser_test_2
{
	for TEST_NUMBER in {4..4};
	do
	$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES unit_tests/test_parser_2.c -DTEST=$TEST_NUMBER $MANUALLY_ADDED_LIBFT
	$VALGRIND
	./a.out >> logs/result_parser.log
	done
}

if [[ $1 != "SOURCE" ]]; then
	check_norminette
	prepare_logs_dir
	make test
	./test
	make -s lib/libft/libft.a
	echo -e "====\t\t$(date +%d\ %b\ %Y\ @\ %T)\t\t====" > logs/result_parser.log
	run_parser_test_1
	run_parser_test_2
	echo -e "====\t\t\tEND of the log\t\t\t====" >> logs/result_parser.log
	feedback
	$RM a.out
fi