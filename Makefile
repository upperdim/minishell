NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code
ifeq ($(DEBUG), 1)
CFLAGS += -g3
re : fclean all
endif

LIB_DIR = lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft -lreadline

HEADERS_DIR = includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))

all: $(NAME)
.PHONY: all


################################################################################
# Source files
################################################################################
BUILTIN_FILES = cd.c pwd.c echo.c env.c export.c unset.c exit.c builtins.c\
	builtins_utils.c
BUILTINS = $(addprefix builtins/, $(BUILTIN_FILES))

UTILS_FILES = signal_handler.c prompt.c exit_error.c env_utils.c token_utils.c\
	list_int.c str_utils.c str_append.c ft_atol.c add_token_utils.c
UTILS = $(addprefix utils/, $(UTILS_FILES))

EXEC_FILES = exec.c exec_utils.c heredoc.c divide_tokens.c redirections.c\
	heredoc_expansion.c
EXEC = $(addprefix exec/, $(EXEC_FILES))

_EXPANSION_TILDA = detect_tilda.c exp_tilda.c
EXPANSION_TILDA = $(addprefix tilda/, $(_EXPANSION_TILDA))

_EXPANSION_VAR = exp_var.c exp_var2.c var_utils.c detect_var.c
EXPANSION_VAR = $(addprefix var/, $(_EXPANSION_VAR))

_EXPANSION = $(EXPANSION_TILDA) $(EXPANSION_VAR)
EXPANSION = $(addprefix expansion/, $(_EXPANSION))

_TOKENIZER = tokenizer.c token_rules.c tokenizer_quotes_redirs.c\
	str_append_tok.c
TOKENIZER = $(addprefix tokenization/, $(_TOKENIZER))

PARSER_FILES = parser.c merge_quotes.c exit_error.c $(EXPANSION) $(TOKENIZER)
PARSER = $(addprefix parser/, $(PARSER_FILES))

_SRC = main.c $(EXEC) $(PARSER) $(BUILTINS) $(UTILS)
SRC = $(addprefix src/, $(_SRC))


################################################################################
# Creating binaries
################################################################################
OBJ = $(SRC:src/%.c=bin/%.o)

bin:
	@mkdir -p bin/builtins\
		bin/exec\
		bin/parser/expansion/tilda\
		bin/parser/expansion/var\
		bin/parser/tokenization\
		bin/utils

bin/%.o:src/%.c | bin
	@printf "%-100s\r" "	Compiling $@"
	@mkdir -p bin/builtins bin/exec bin/parser bin/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) $(COLOR_FLAG)


################################################################################
# Rules
################################################################################

$(NAME) : $(LIBFT_PATH)/libft.a $(OBJ) includes/minishell.h
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."

$(LIBFT_PATH)/libft.a:
	@git submodule update --init --recursive $(LIBFT_PATH)
	@printf "%-100s\r" "	Creating libft.a..."
	@make -C $(LIBFT_PATH) --silent;

clean:
	@printf "%-100s\r" "	Erasing binaries..."
	@$(RM) $(OBJ) $(OBJ_BUILTINS)
	@$(RM) bin/
	@$(RM) bin_builtins
	@make -C $(LIBFT_PATH) clean
.PHONY: clean

fclean: clean
	@printf "%-100s\r" "	Erasing $(NAME)..."
	@$(RM) $(NAME)
	@$(RM) $(NAME)_builtins
	@make -C $(LIBFT_PATH) fclean
.PHONY: fclean

re: fclean all
.PHONY: re

bonus: $(NAME)_bonus
.PHONY: bonus

$(NAME)_bonus: $(LIBFT_PATH)/libft.a $(OBJ)
	@printf "%-100s\r" "	Compiling $(NAME) with bonus..."
	@$(CC) -o $(NAME)_bonus $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."


################################################################################
# Unit test
################################################################################
clean_test:
	@$(RM) $(OBJ_TEST)
	@printf "%-100s\r" "	Erasing builtin_test binaries..."
	@$(RM) tests/builtins_test/bin/
.PHONY: clean_test

fclean_test: clean_test
	@printf "%-100s\r" "	Erasing builtin_test..."
	@$(RM) builtin_test
.PHONY: fclean_test

re_test: fclean_test builtin_test
.PHONY: re_test

tests/builtins_test/bin/%.o : tests/builtins_test/%.c tests/run_tests.sh
	@mkdir -p tests/builtins_test/bin
	@printf "%-100s\r" "	Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

builtin_test: $(LIBFT_PATH)/libft.a $(OBJ_TEST)
	@$(RM) bin/utils/prompt.o
	@make bin/utils/prompt.o COLOR=0
	@$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."

update_tests:
	@cd tests && git checkout main && git pull origin main
.PHONY: update_tests

tests/run_tests.sh:
	@git submodule update --init --recursive tests
	@cd tests && git checkout main *

test: | tests/run_tests.sh
	@./tests/run_tests.sh
.PHONY: test


################################################################################
# Parser tests
################################################################################
SRC_TEST = tests_parser/test_parser.c
TEST_OBJS = $(filter-out bin/main.o, $(OBJ)) $(SRC_TEST:%.c=%.o)

%.o: %.c
	@printf "%-100s\r" "	Compiling $@"
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) $(COLOR_FLAG)

test_parser: $(LIBFT_PATH)/libft.a $(TEST_OBJS) includes/minishell.h
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(LDFLAGS) $(INCLUDES) -o $@
