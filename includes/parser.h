/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/19 21:12:58 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# define ERR_MSG_UNCLOSED_QUOTES ("minishell: SyntaxError: unclosed quotes\n")
# define ERR_MSG_INVALID_TOKENS ("minishell: SyntaxError: invalid tokens\n")
# define ERR_MSG_MALLOC ("minishell: Error allocating memory: malloc\n")

# define NOT_QUOTE 0

typedef enum e_token_type
{
	STRING,
	REDIR_TO,
	APPEND_TO,
	REDIR_FROM,
	HERE_DOC,
	PIPE,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_list_int
{
	int					val;
	struct s_list_int	*next;
	struct s_list_int	*prev;
}	t_list_int;


/* Parser variables */
typedef struct s_pvars
{
	char	*line;
	int		len;
	t_token	*head;
}	t_pvars;

t_token	*parse(char *line);
t_token	*tokenize(char *line);
int		check_token_rules(t_token *head);
int		merge_quotes(t_token *token_list);

int		detect_tilda_expansions(char *line, int len, t_list_int **p_tilda_idxs_to_expand);
int		detect_var_expansions(char *line, t_list_int **p_var_idxs_to_exp, int s);

void	expand_tilda(t_token *token_list, t_list_int *tilda_idxs_to_expand, const int list_size);
void	expand_var(t_token *token_list, t_list_int *var_idxs_to_expand, const int list_size);

#endif