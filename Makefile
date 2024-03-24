# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 19:23:27 by JFikents          #+#    #+#              #
#    Updated: 2024/03/24 18:46:14 by JFikents         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code


LIB_DIR = lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft -lreadline


HEADERS_DIR = includes/ $(LIBFT_PATH)/includes/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))


BUILTIN_FILES = cd.c pwd.c echo.c env.c export.c unset.c exit.c builtins.c
BUILTINS = $(addprefix builtins/, $(BUILTIN_FILES))

UTILS_FILES = signal_handler.c prompt.c prompt_no_color.c
UTILS = $(addprefix utils/, $(UTILS_FILES))

EXEC_FILES = exec.c pipe_utils.c
EXEC = $(addprefix exec/, $(EXEC_FILES))

PARSER_FILES = parser.c
PARSER = $(addprefix parser/, $(PARSER_FILES))

C_FILES = main.c main_builtins.c $(EXEC) $(PARSER) $(BUILTINS) $(UTILS)

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(C_FILES))

OBJ = $(SRC:src/%.c=bin/%.o)
B_OBJ = $(SRC:src/%.c=bin_b/%.o)


all: $(NAME) $(NAME)_builtins
.PHONY: all

NO_COLOR ?= 0
ifeq ($(NO_COLOR),0)
bin/%.o : src/%.c #bin
	@echo "	Compiling $@"
	@mkdir -p bin/builtins bin/exec bin/parser bin/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

bin_b/%.o : src/%.c #bin_b
	@echo "	Compiling $@"
	@mkdir -p bin_b/builtins bin_b/exec bin_b/parser bin_b/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) -DBUILTINS
else
bin/%.o : src/%.c #bin
	@echo "	Compiling $@"
	@mkdir -p bin/builtins bin/exec bin/parser bin/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) -DNO_COLOR

bin_b/%.o : src/%.c #bin_b
	@echo "	Compiling $@"
	@mkdir -p bin_b/builtins bin_b/exec bin_b/parser bin_b/utils
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES) -DBUILTINS -DNO_COLOR
endif

$(NAME) : lib/libft/libft.a $(OBJ) includes/minishell.h
	@echo "	Compiling $@..."
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

$(NAME)_builtins : lib/libft/libft.a $(B_OBJ) includes/minishell.h
	@echo "	Compiling $@..."
	@$(CC) -o $@ $(B_OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

lib/libft/libft.a:
	@git submodule update --init --recursive
	@echo "	Creating libft.a..."
	@make -C $(LIBFT_PATH) --silent;

clean:
	@echo "	Ereasing binaries..."
	@$(RM) $(OBJ+) $(OBJ) $(B_OBJ)
	@$(RM) bin/
	@$(RM) bin_b
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

# Debug
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

# UNIT TESTS
TEST_FILES = test_main.c
T_SRC = $(addprefix tests/, $(TEST_FILES))
T_OBJ = $(T_SRC:tests/%.c=tests/bin/%.o) $(filter-out bin/main%, $(OBJ))

clean_test:
	@echo "	Ereasing test binaries..."
	@$(RM) $(T_OBJ)
	@$(RM) tests/bin/
.PHONY: clean_test

fclean_test: clean_test
	@echo "	Ereasing test..."
	@$(RM) test
.PHONY: fclean_test

re_test: fclean_test test
.PHONY: re_test

tests/bin:
	@mkdir -p tests/bin

tests/bin/%.o : tests/%.c tests/bin
	@echo "	Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

test: lib/libft/libft.a $(T_OBJ)
	@echo "	Compiling tests..."
	@$(CC) -o test $^ $(CFLAGS) $(INCLUDES) $(LDFLAGS)
