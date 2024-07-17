# Libft
LIBFT_PATH		= lib/libft/
LIBFT			= $(LIBFT_PATH)libft.a

# Sources
BUILTIN_FILES	= cd.c pwd.c echo.c env.c export.c unset.c exit.c builtins.c\
					builtins_utils.c
UTILS_FILES		= signal_handler.c prompt.c exit_error.c env_utils.c \
					token_utils.c list_int.c str_utils.c str_append.c ft_atol.c\
					
EXEC_FILES		= exec.c exec_utils.c heredoc.c divide_tokens.c redirections.c
PARSER_FILES	= parser.c expansion/exp_tilda.c expansion/exp_var.c \
					tokenizer/tokenizer.c

BUILTINS		= $(addprefix builtins/, $(BUILTIN_FILES))
UTILS			= $(addprefix utils/, $(UTILS_FILES))
EXEC			= $(addprefix exec/, $(EXEC_FILES))
PARSER			= $(addprefix parser/, $(PARSER_FILES))

SRCS_NO_MAIN	= $(EXEC) $(PARSER) $(BUILTINS) $(UTILS)
SRCS			= $(SRCS_NO_MAIN) src/main.c

# Compilation
OBJ_DIR         = bin
OBJS			= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
NAME			= minishell

CC				= cc
CFLAGS			= -Wextra -Wall -Werror
LIBS			= -L$(LIBFT_PATH) -lft -lreadline
INC				= -I includes/ -I $(LIBFT_PATH)/includes/

# VPATH to specify directories where make will look for source files
vpath %.c builtins utils exec parser src parser/expansion tests_parser

all:			$(NAME)

$(NAME):		$(OBJS) $(LIBFT)
				@echo "Compiling minishell..."
				@$(CC) $(OBJS) $(LIBS) $(INC) -o $(NAME)

$(LIBFT):
				@echo "Making libft..."
				@make -sC $(LIBFT_PATH) all

# Ensure object directories are created as needed
$(OBJ_DIR)/%.o: %.c
				@mkdir -p $(dir $@)
				@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
				@echo "Cleaning object files..."
				@make -sC $(LIBFT_PATH) clean
				@rm -rf $(OBJ_DIR)/*
				@rm -rf test_parser

fclean: clean
				@echo "Cleaning minishell..."
				@make -sC $(LIBFT_PATH) fclean
				@rm -rf $(NAME)

# Parser test
SRCS_TEST_PARSER = $(SRCS_NO_MAIN) tests_parser/test_parser.c
TEST_OBJS        = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_TEST_PARSER))
test_parser:	$(TEST_OBJS) $(LIBFT)
				@echo "Compiling parser tests..."
				@$(CC) $(TEST_OBJS) $(LIBS) $(INC) -o test_parser
