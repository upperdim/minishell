/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/20 11:09:59 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

/**
	@brief Enum for the different types of tokens
	@param CMD Command token, any string that is not a special token
	@param PIPE Redirects `STDOUT_FILENO` from `CMD` 1 to `STDIN_FILENO` from
		`CMD` 2;
		SYNTAX: `CMD` 1 | `CMD` 2.
		NOTE: The space character after and before the pipe is optional
	@param REDIR_FROM Creates the `FD` (File Descriptor) and sets it as
		`STDIN_FILENO` for `CMD` if there is a `CMD` at the left side;
		SYNTAX: `CMD`(optional) < `FILEPATH`.
		NOTE: The space character after and before the '<' character are
			optional.
	@param REDIR_TO Redirects the `STDOUT_FILENO` (if there is not other `FD`)
		from `CMD` to the `FILEPATH`, creating it, or truncating it to 0 if it
		already exists;
		SYNTAX: `CMD`(optional) `FD`(optional)> `FILEPATH`.
		NOTE: The space character after and before the '>' character is optional
			for the `CMD` and `FILEPATH`, but it is not allowed for the `FD`.
			If there is a `FD` there must be a space character separating it
			from the `CMD`.
	@param APPEND_TO Redirects the `STDOUT_FILENO` (if there is not other `FD`)
		from `CMD` to the `FILEPATH`, appending it to the end of the file or
		creating it if it does not exist;
		SYNTAX: `CMD`(optional) `FD`(optional)>> `FILEPATH`.
		NOTE: The space character after and before the '>>' character is optional
			for the `CMD` and `FILEPATH`, but it is not allowed for the `FD`.
			If there is a `FD` there must be a space character separating it
			from the `CMD`.
	@param HERE_DOC Saves all the input from the user until the `LIMITER` is
		reached, then it substitutes the `STDIN_FILENO` (if there is not
		other `FD`) with the temporary file created with the input, to be used
		by the `CMD`, and then it deletes the temporary file;
		SYNTAX: `CMD`(optional) `FD`(optional)<< `LIMITER`.
		NOTE: The space character after and before the '<<' character is
			optional for the `CMD` and `LIMITER`, but it is not allowed for the
			`FD`. If there is a `FD` there must be a space character separating
			it from the `CMD`.
	@param DOUBLE_QUOTES Prevents the interpretation of the special characters
		inside the quotes, except for the `$` character, which allows the
		expansion of the environment variables;
		SYNTAX: `"STRING"`.
	@param SINGLE_QUOTES Prevents the interpretation of the special characters
		inside the quotes;
		SYNTAX: `'STRING'`.
 */
enum	e_token
{
	STRING,
	CMD,
	PIPE,
	REDIR_FROM,
	REDIR_TO,
	APPEND_TO,
	HERE_DOC,
	DOUBLE_QUOTES,
	SINGLE_QUOTES,
};

typedef struct s_split
{
	char			*result;
	enum e_token	token;
	struct s_split	*next;
	struct s_split	*prev;
}	t_split;

typedef struct s_flags
{
	int		pipe_in;
	int		pipe_out;
	int		redir;
}	t_flags;

typedef struct s_instruction
{
	char					*cmd;
	char					**args;
	int						and_index;
	struct s_instruction	*next;
	t_flags					flags;
}	t_instruction;

t_instruction	*parse_line(char *line);
t_split			*ft_create_tokens(char *input);
void			ft_free_split(t_split *split);
void			ft_expand_env_var(char *input, int index, t_split *new,
					const char *end_point);
char			*ft_find_limit(char *input);
int				ft_count_spaces(char *input);
int				ft_init_next_token_if_space(char *input, t_split **new);

#endif