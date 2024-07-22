/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 07:42:00 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# define ERR_MSG_UNCLOSED_QUOTES "minishell: SyntaxError: unclosed quotes\n"
# define ERR_MSG_INVALID_TOKENS "minishell: SyntaxError: invalid tokens\n"
# define ERR_MSG_MALLOC "minishell: Error allocating memory: malloc\n"

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

typedef struct s_exp_idxs
{
	t_list_int	*tld_idxs;
	t_list_int	*var_idxs;
}	t_exp_idxs;

typedef struct s_tokenizer_vars
{
	char		*line;
	int			i;
	char		*curr_token_val;
	t_token		**p_head;
	t_exp_idxs	*free_on_err;
}	t_tokenizer_vars;

// Parsing
t_token	*parse(char *line);
t_token	*tokenize(char *line, t_exp_idxs *exp_idxs);
int		check_token_rules(t_token *head);
int		merge_quotes(t_token *token_list, t_exp_idxs *exp_idxs);

// Tokenizer helper functions
void	handle_quotes(t_tokenizer_vars *v, int idx_dist_to_quot);
void	handle_redirs(t_tokenizer_vars *v);
void	add_numeric_redir_token(\
t_tokenizer_vars *v, char redir_type, int single_or_double);

// Expansion detections
int		detect_tld_exp(char *line, int len, t_list_int **p_tld_idxs);
int		detect_var_exp(\
char *line, t_list_int **p_var_idxs, int s, int var_idx);

// Expansions
void	expand_tilda(t_token *tok_lst, t_exp_idxs *exp_idxs);
void	expand_var(t_token *tok_lst, t_list_int *var_idxs, const int lst_siz);

// Variable expansion utils
int		is_valid_var_exp_char(char c);
int		is_prev_here_doc(t_token *tok);
void	replace_tok_val_section(\
t_token *tok, int s, int e, char *replace_with, int *p_value_len);

// String append wrappers for tokenization
void	str_append_tok(char **p_str, char *to_append, t_tokenizer_vars *v);
void	str_appendc_tok(char **p_str, char char_to_append, t_tokenizer_vars *v);
void	str_append_free_tok(\
char **p_str, char *to_append_and_free, t_tokenizer_vars *v);

// Error management
void	exit_free_exp_idxs(char *err_msg, t_exp_idxs *exp_idxs);
void	exit_free_tokenizer(char *err_msg, t_tokenizer_vars *v);
void	exit_free_toklst_exp_idxs(t_token *tok_lst, t_exp_idxs *exp_idxs);

#endif