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

PARSER_FILES = parser.c
PARSER = $(addprefix parser/, $(PARSER_FILES))

SRC_NO_MAIN = $(EXEC) $(PARSER) $(BUILTINS) $(UTILS)


################################################################################
# Creating binaries
################################################################################
SRC_MAIN = main.c $(SRC_NO_MAIN)
SRC_TEST_MAIN = test_main.c test_builtins.c test_echo.c test_echo_2.c\
	test_exit.c test_utils.c
SRC_BUILTINS_MAIN = main_builtins.c $(SRC_NO_MAIN)

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_MAIN))
SRC_TEST = $(addprefix tests/, $(SRC_TEST_MAIN))
SRC_BUILTINS = $(addprefix $(SRC_DIR), $(SRC_BUILTINS_MAIN))

OBJ = $(SRC:src/%.c=bin/%.o)
OBJ_TEST = $(SRC_TEST:tests/%.c=tests/bin/%.o) $(filter-out bin/main.o, $(OBJ))
OBJ_BUILTINS = $(SRC_BUILTINS:src/%.c=bin_builtins/%.o)


################################################################################
# Rules
################################################################################
all: $(NAME) $(NAME)_builtins
.PHONY: all

bin/%.o : src/%.c
	@echo "	Compiling $@"
	@mkdir -p bin/builtins bin/exec bin/parser bin/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) $(COLOR_FLAG)

$(NAME) : lib/libft/libft.a $(OBJ) includes/minishell.h
	@echo "	Compiling $@..."
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

lib/libft/libft.a:
	@git submodule update --init --recursive
	@echo "	Creating libft.a..."
	@make -C $(LIBFT_PATH) --silent;

clean:
	@echo "	Ereasing binaries..."
	@$(RM) $(OBJ+) $(OBJ) $(OBJ_BUILTINS)
	@$(RM) bin/
	@$(RM) bin_builtins
	@make -C $(LIBFT_PATH) clean
.PHONY: clean

fclean: clean
	@echo "	Ereasing $(NAME)..."
	@$(RM) $(NAME)
	@$(RM) $(NAME)_builtins
	@make -C $(LIBFT_PATH) fclean
.PHONY: fclean

re: fclean all
.PHONY: re

bonus: lib/libft/libft.a $(OBJ+) $(OBJ)
	@echo "	Compiling $(NAME) with bonus..."
	@$(CC) -o $(NAME) $(OBJ+) $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)


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
	@$(CC) $(CFLAGS) $(SRC) $(DEBUG_FLAGS) $(INCLUDES) $(LDFLAGS)
	@mv a.out.dSYM $(DEBUG_DIR)
	@mv a.out $(DEBUG_DIR)


################################################################################
# Unit test
################################################################################
clean_test:
	@$(RM) $(OBJ_TEST)
		@echo "	Ereasing test binaries..."
	@$(RM) tests/bin/
.PHONY: clean_test

fclean_test: clean_test
	@echo "	Ereasing test..."
	@$(RM) test
.PHONY: fclean_test

re_test: fclean_test test
.PHONY: re_test

tests/bin/%.o : tests/%.c
	@mkdir -p tests/bin
	@echo "	Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

test: lib/libft/libft.a $(OBJ_TEST)
	@$(RM) bin/utils/prompt.o
	@make bin/utils/prompt.o COLOR=0
	@echo "	Compiling tests..."
	@$(CC) -o test $^ $(CFLAGS) $(INCLUDES) $(LDFLAGS)


################################################################################
# Builtin test
################################################################################
bin_builtins/%.o : src/%.c
	@echo "	Compiling $@"
	@mkdir -p bin_builtins/builtins bin_builtins/exec bin_builtins/parser bin_builtins/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) $(COLOR_FLAG)

$(NAME)_builtins : lib/libft/libft.a $(OBJ_BUILTINS) includes/minishell.h
	@echo "	Compiling $@..."
	@$(CC) -o $@ $(OBJ_BUILTINS) $(CFLAGS) $(INCLUDES) $(LDFLAGS)


################################################################################
# Colors
################################################################################
COLOR ?= 1
ifeq ($(COLOR),1)
COLOR_FLAG = -DCOLOR
else
COLOR_FLAG = 
endif
