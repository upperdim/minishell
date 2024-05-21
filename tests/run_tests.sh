#! /bin/bash
source tests/utils_functions.sh

CC=cc
RM="rm -rf"
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"
INCLUDES="-Iincludes -Ilib/libft/includes -Itests/includes"
LIBRARIES="-Llib/libft -lft"
# COLORS ARE DEFINED IN tests/utils_functions.sh

# DEBUG MODE
DEBUG="-g3"
if [[ "$1" == "d" || "$2" == "d" ]]; then
	CFLAGS="$CFLAGS $DEBUG"
	echo -e "$BOLD_YELLOW Debug mode enabled$DEFAULT"
fi
if [[ "$(uname)" == "Linux" ]]; then
	MANUALLY_ADDED_LIBFT="lib/libft/libft.a"
fi


PARSER_FILES="src/parser/parser.c src/parser/ft_create_tokens.c\
	src/parser/create_tokens_utilities.c src/parser/ft_tokenize_pipe.c\
	tests/src/unit_tests_utils.c"

function run_parser_test_1
{
	for TEST_NUMBER in {1..5};
	do
		$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES tests/src/test_parser.c -DTEST=$TEST_NUMBER $MANUALLY_ADDED_LIBFT
		if [[ ! -x a.out ]]; then
			echo -e "$BOLD_RED Failed compilation for test $TEST_NUMBER$DEFAULT"
			echo -e "\tFailed compilation for test $TEST_NUMBER" >> tests/logs/result_parser.log
			continue
		fi
		./a.out >> tests/logs/result_parser.log
		if [[ "$(uname)" == "Linux" ]]; then
			run_valgrind parser $TEST_NUMBER
		fi
		echo >> tests/logs/result_parser.log
		$RM a.out
	done
	if [[ $1 -ge 1 && $1 -le 5 ]]; then
		$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES tests/src/test_parser.c -DTEST=$1 $MANUALLY_ADDED_LIBFT
		echo -e "$BOLD_YELLOW Test $1 ready for debug$DEFAULT"
	fi
}

function run_parser_test_2
{
	for TEST_NUMBER in {6..10};
	do
		$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES tests/src/test_parser_2.c -DTEST=$TEST_NUMBER $MANUALLY_ADDED_LIBFT
		if [[ ! -x a.out ]]; then
			echo -e "$BOLD_RED Failed compilation for test $TEST_NUMBER$DEFAULT"
			echo -e "\tFailed compilation for test $TEST_NUMBER" >> tests/logs/result_parser.log
			continue
		fi
		./a.out >> tests/logs/result_parser.log
		if [[ "$(uname)" == "Linux" ]]; then
			run_valgrind parser $TEST_NUMBER
		fi
		echo >> tests/logs/result_parser.log
		$RM a.out
	done
	if [[ $1 -ge 6 && $1 -le 10 ]]; then
		$CC $CFLAGS $INCLUDES $LIBRARIES $PARSER_FILES tests/src/test_parser_2.c -DTEST=$1 $MANUALLY_ADDED_LIBFT
		echo -e "$BOLD_YELLOW Test $1 ready for debug$DEFAULT"
	fi
}

function run_builtin_test
{
	make -s builtin_test 2> tests/logs/minishell_builtins_results.log 1> /dev/null
	if [[ ! -x builtin_test ]]; then
		echo -e "$BOLD_RED Failed compilation for builtin_test$DEFAULT"
		echo -e "$YELLOW\tFor more information check tests/logs/minishell_builtins_results.log$DEFAULT"
		exit 1
	fi
	./builtin_test > tests/logs/minishell_builtins_results.log
	if [[ "$(cat tests/logs/minishell_builtins_results.log | grep -c "failed")" > 0 ]]; then
		echo -e "$BOLD_RED Failed one or more builtin tests$DEFAULT"
		echo -e "$YELLOW\tFor more information see tests/logs/minishell_builtins_results.log$DEFAULT"
	else
		echo -e "$BOLD_GREEN All builtin tests passed successfully$DEFAULT"
	fi
}

if [[ $1 != "SOURCE" ]]; then
	check_norminette
	prepare_logs_dir
	run_builtin_test
	make -s lib/libft/libft.a
	echo -e "====\t\t\t\t$(date +%d\ %b\ %Y\ @\ %T)\t\t\t\t====\n" > tests/logs/result_parser.log
	run_parser_test_1
	run_parser_test_2
	# NEXT TESTS TO BE ADDED HERE
		# echo 1&&echo 2
		#	EXPECTED: 1\n2
		# echo "1&&"echo 2
		#	EXPECTED: 1&&echo 2
	echo -e "====\t\t\t\t\tEND of the log\t\t\t\t\t====" >> tests/logs/result_parser.log
	feedback
	$RM a.out
	make -s fclean_test
fi