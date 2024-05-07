#! /bin/bash
source unit_tests/utils_functions.sh

CC=cc
CFLAGS="-Wall -Wextra -Werror -Wunreachable-code"
INCLUDES="-Iincludes -Ilib/libft/includes"
LIBRARIES="-Llib/libft -lft"

check_norminette
prepare_logs_dir
make test
./test
make -s lib/libft/libft.a
$CC $CFLAGS $INCLUDES $LIBRARIES unit_tests/test_parser.c src/parser/parser.c
echo -e "====\t\t$(date +%d\ %b\ %Y\ @\ %T)\t\t====" > logs/result_parser.log
./a.out >> logs/result_parser.log
$CC $CFLAGS $INCLUDES $LIBRARIES unit_tests/test_parser.c src/parser/parser.c -DTEST=1
./a.out >> logs/result_parser.log
echo -e "====\t\t\tEND of the log\t\t\t====" >> logs/result_parser.log
feedback
$RM a.out