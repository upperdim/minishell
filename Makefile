# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 19:23:27 by JFikents          #+#    #+#              #
#    Updated: 2024/03/17 14:52:06 by JFikents         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code


LIB_DIR = lib
LIBFT_PATH = $(LIB_DIR)/libft
LDFLAGS = -L$(LIBFT_PATH) -lft -lreadline


HEADERS_DIR = includes/ $(LIBFT_PATH)/h_files/
INCLUDES = $(addprefix -I, $(HEADERS_DIR))


BUILTIN_FILES = cd.c pwd.c echo.c env.c export.c unset.c exit.c builtins.c
BUILTINS = $(addprefix builtins/, $(BUILTIN_FILES))

UTILS_FILES = error_handler.c malloc_utils.c signal_handler.c prompt.c
UTILS = $(addprefix utils/, $(UTILS_FILES))

EXEC_FILES = exec.c
EXEC = $(addprefix exec/, $(EXEC_FILES))

PARSER_FILES = parser.c
PARSER = $(addprefix parser/, $(PARSER_FILES))

C_FILES = main.c $(EXEC) $(PARSER) $(BUILTINS) $(UTILS)

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(C_FILES))

OBJ = $(SRC:%.c=%.o)
OBJ+ = $(BONUS_SRC:.c=.o)


all: $(NAME)

$(NAME) : lib/libft/libft.a $(OBJ)
	@echo "	Compiling $@..."
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

%.o : %.c
	@echo "	Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

lib/libft/libft.a:
	@git submodule update --init --recursive
	@echo "	Creating libft.a..."
	@make -C $(LIBFT_PATH) --silent;

clean:
	@echo "	Ereasing Files .o"
	@$(RM) $(OBJ+) $(OBJ)
.PHONY: clean

fclean: clean
	@echo "	Ereasing $(NAME)..."
	@$(RM) $(NAME)
	@make -C $(LIBFT_PATH) fclean
.PHONY: fclean

re: fclean all
.PHONY: re

bonus: lib/libft/libft.a $(OBJ+) $(OBJ)
	@echo "	Compiling $(NAME) with bonus..."
	@$(CC) -o $(NAME) $(OBJ+) $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

# Debug
DEBUG_DIR = debugger
DEBUG_FLAGS = -fsanitize=address -g3

c:
	@$(RM) $(DEBUG_DIR)/* 
	@$(RM) *.out *.dSYM *.gch test
.PHONY: c

debug: $(DEBUG_DIR)/a.out
.PHONY: debug

$(DEBUG_DIR)/a.out: lib/libft/libft.a includes/minishell.h
	@$(CC) $(CFLAGS) $(SRC) $(DEBUG_FLAGS) $(INCLUDES) $(LDFLAGS)
	@mv a.out.dSYM $(DEBUG_DIR)
	@mv a.out $(DEBUG_DIR)
