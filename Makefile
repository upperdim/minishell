NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code

LIB_DIR = lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft -lreadline

HEADERS_DIR = includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))


################################################################################
# Source files
################################################################################
BUILTIN_FILES = cd.c pwd.c echo.c env.c export.c unset.c exit.c builtins.c
BUILTINS = $(addprefix builtins/, $(BUILTIN_FILES))

UTILS_FILES = signal_handler.c prompt.c
UTILS = $(addprefix utils/, $(UTILS_FILES))

EXEC_FILES = exec.c pipe_utils.c
EXEC = $(addprefix exec/, $(EXEC_FILES))

PARSER_FILES = parser.c ft_create_tokens.c create_tokens_utilities.c\
	ft_tokenize_pipe.c
PARSER = $(addprefix parser/, $(PARSER_FILES))

SRC_NO_MAIN = $(EXEC) $(PARSER) $(BUILTINS) $(UTILS)


################################################################################
# Creating binaries
################################################################################
SRC_MAIN = main.c $(SRC_NO_MAIN)
SRC_TEST_MAIN = main_test.c test_builtins.c test_echo.c test_echo_2.c\
	test_exit.c test_utils.c test_cd.c
SRC_BUILTINS_MAIN = main_builtins.c $(SRC_NO_MAIN)

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_MAIN))
SRC_TEST = $(addprefix tests/builtins_test/, $(SRC_TEST_MAIN))
SRC_BUILTINS = $(addprefix $(SRC_DIR), $(SRC_BUILTINS_MAIN))

OBJ = $(SRC:src/%.c=bin/%.o)
OBJ_TEST = $(SRC_TEST:tests/builtins_test/%.c=tests/builtins_test/bin/%.o)\
	$(filter-out bin/main.o, $(OBJ))
OBJ_BUILTINS = $(SRC_BUILTINS:src/%.c=bin_builtins/%.o)


################################################################################
# Rules
################################################################################
all: $(NAME) $(NAME)_builtins
.PHONY: all

bin/%.o : src/%.c
	@printf "%-100s\r" "	Compiling $@"
	@mkdir -p bin/builtins bin/exec bin/parser bin/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) $(COLOR_FLAG)

$(NAME) : lib/libft/libft.a $(OBJ) includes/minishell.h
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."

lib/libft/libft.a:
	@git submodule update --init --recursive
	@printf "%-100s\r" "	Creating libft.a..."
	@make -C $(LIBFT_PATH) --silent;

clean:
	@printf "%-100s\r" "	Erasing binaries..."
	@$(RM) $(OBJ+) $(OBJ) $(OBJ_BUILTINS)
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

bonus: lib/libft/libft.a $(OBJ+) $(OBJ)
	@printf "%-100s\r" "	Compiling $(NAME) with bonus..."
	@$(CC) -o $(NAME) $(OBJ+) $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."


################################################################################
# Debug
################################################################################
DEBUG_DIR = debug
DEBUG_FLAGS = -fsanitize=address -g3

c:
	@$(RM) $(DEBUG_DIR)/* 
	@$(RM) *.out *.dSYM *.gch test
.PHONY: c

debug: $(DEBUG_DIR)/a.out
.PHONY: debug

$(DEBUG_DIR)/a.out: c lib/libft/libft.a includes/minishell.h
	@$(CC) $(CFLAGS) $(SRC_TEST) $(DEBUG_FLAGS) $(INCLUDES) $(LDFLAGS) $(filter-out src/main.c, $(SRC))
	@mv a.out.dSYM $(DEBUG_DIR)
	@mv a.out $(DEBUG_DIR)


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

tests/builtins_test/bin/%.o : tests/builtins_test/%.c
	@mkdir -p tests/builtins_test/bin
	@printf "%-100s\r" "	Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

builtin_test: lib/libft/libft.a $(OBJ_TEST)
	@$(RM) bin/utils/prompt.o
	@make bin/utils/prompt.o COLOR=0
	@$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."


test:
	@./tests/test_suit.sh
.PHONY: test


################################################################################
# Builtin test
################################################################################
bin_builtins/%.o : src/%.c
	@printf "%-100s\r" "	Compiling $@"
	@mkdir -p bin_builtins/builtins bin_builtins/exec bin_builtins/parser bin_builtins/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) $(COLOR_FLAG)

$(NAME)_builtins : lib/libft/libft.a $(OBJ_BUILTINS) includes/minishell.h
	@$(CC) -o $@ $(OBJ_BUILTINS) $(CFLAGS) $(INCLUDES) $(LDFLAGS)
	@printf "\033[1;33m %-100s \033[0m\n" "$@ is ready to be use."


################################################################################
# Colors
################################################################################
COLOR ?= 1
ifeq ($(COLOR),1)
COLOR_FLAG = -DCOLOR
else
COLOR_FLAG = 
endif
