# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 19:23:27 by JFikents          #+#    #+#              #
#    Updated: 2024/03/15 17:01:15 by JFikents         ###   ########.fr        #
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


C_FILES = parser/parser.c main.c error_handler.c exec.c
SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(C_FILES))


OBJ = $(addprefix $(SRC_DIR), $(C_FILES:.c=.o))
OBJ+ = $(addprefix $(SRC_DIR), $(BONUS_FILES:.c=.o))


all: $(NAME)

$(NAME) : fetch_libft $(OBJ)
	@echo "	Compiling $@..."
	@$(CC) -o $@ $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

%.o : %.c
	@echo "	Compiling $@..."
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

fetch_libft: submodule
	@echo "	fetching libft..."
	@make -C $(LIBFT_PATH) --silent;
.PHONY: fetch_libft

submodule:
	@git submodule update --init --recursive
.PHONY: submodule

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

bonus: fetch_libft $(OBJ+) $(OBJ)
	@echo "	Compiling $(NAME) with bonus..."
	@$(CC) -o $(NAME) $(OBJ+) $(OBJ) $(CFLAGS) $(INCLUDES) $(LDFLAGS)

# Debug
DEBUGGER = debugger/
DEBUG_FLAGS = -fsanitize=address -g3
c:
	@$(RM) $(DEBUGGER)* 
	@$(RM) *.out *.dSYM *.gch test
.PHONY: c
debug: c a_files
	@$(CC) $(CFLAGS) $(SRC) $(DEBUG_FLAGS) $(INCLUDES) $(LDFLAGS)
	@mv a.out.dSYM $(DEBUGGER)
	@mv a.out $(DEBUGGER)
.PHONY: debug
