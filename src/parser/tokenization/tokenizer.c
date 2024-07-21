/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:53:39 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 00:12:30 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_numeric_redir_token(\
t_tokenizer_vars *v, char redir_type, int single_or_double)
{
	char	*new_val;
	int		new_type;

	new_type = -1;
	new_val = NULL;
	str_append(&new_val, v->curr_token_val);
	str_appendc(&new_val, redir_type);
	if (single_or_double == 2)
		str_appendc(&new_val, redir_type);
	if (redir_type == '>')
	{
		if (single_or_double == 1)
			new_type = REDIR_TO;
		else if (single_or_double == 2)
			new_type = APPEND_TO;
	}
	else if (redir_type == '<')
	{
		if (single_or_double == 1)
			new_type = REDIR_FROM;
		else if (single_or_double == 2)
			new_type = HERE_DOC;
	}
	add_token(v->p_head, new_type, new_val, v->free_on_err);
	free(new_val);
}

// TODO: Do we need to get a pointer to curr_token_val like the other functions?
// Why does this work while others don't?
static void	handle_redirs(t_tokenizer_vars *v)
{
	char	redir_type;

	redir_type = v->line[v->i + 1];
	if (!str_is_numeric(v->curr_token_val))
	{
		add_token(v->p_head, STRING, v->curr_token_val, v->free_on_err);
		v->curr_token_val[0] = '\0';
		return ;
	}
	if (ft_atol(v->curr_token_val) > INT_MAX || ft_atol(v->curr_token_val) < 0)
	{
		add_token(v->p_head, STRING, v->curr_token_val, v->free_on_err);
		v->curr_token_val[0] = '\0';
		return ;
	}
	if (v->line[v->i + 2] != '\0' && v->line[v->i + 2] == redir_type)
	{
		add_numeric_redir_token(v, redir_type, 2);
		(v->i) += 1;
	}
	else
		add_numeric_redir_token(v, redir_type, 1);
	v->curr_token_val[0] = '\0';
	(v->i)++;
}

/*
	Updates `curr_token_val` and adjusts `i` after properly handling quotes.

	Inputs:
	- line              : input line
	- i                 : current index in the line
	- idx_dist_to_quote : adding this to `i` should give index of the opening quote

	Outputs:
	- curr_token_val : updated current token value
	- i              : updated index position in the line  
*/
static void	handle_quotes(t_tokenizer_vars *v, int idx_dist_to_quot)
{
	char	quote_type;
	int		next_quote_idx;

	quote_type = v->line[v->i + idx_dist_to_quot];
	next_quote_idx = str_findc_idx(\
v->line, v->i + idx_dist_to_quot + 1, quote_type);
	if (next_quote_idx == -1)
		exit_free_exp_idxs(ERR_MSG_UNCLOSED_QUOTES, v->free_on_err);
	else if (next_quote_idx == v->i + idx_dist_to_quot + 1)
	{
		if (strlen_null(v->curr_token_val) == 0)
			add_token(v->p_head, STRING, "", v->free_on_err);
		(v->i) += idx_dist_to_quot + 2;
	}
	else
	{
		str_append_free(&v->curr_token_val, \
str_sub(v->line, v->i + idx_dist_to_quot, next_quote_idx));
		(v->i) = next_quote_idx;
	}
}

static void	create_token_if_curr_tok_val_is_not_empty(t_tokenizer_vars *v)
{
	if (strlen_null(v->curr_token_val) > 0)
	{
		add_token(v->p_head, STRING, v->curr_token_val, v->free_on_err);
		v->curr_token_val[0] = '\0';
	}
}

/* These checks shall be true only if it's the first char after a token */
static int	handle_if_first_char(t_tokenizer_vars *v)
{
	if (v->line[v->i] == ' ')
		return (create_token_if_curr_tok_val_is_not_empty(v), TRUE);
	else if (v->line[v->i] == '|')
		return (add_token(v->p_head, PIPE, "|", v->free_on_err), TRUE);
	else if (v->line[v->i] == '<')
	{
		if (v->line[(v->i) + 1] != '<')
			return (add_token(\
v->p_head, REDIR_FROM, "<", v->free_on_err), TRUE);
		return ((v->i)++, add_token(\
v->p_head, HERE_DOC, "<<", v->free_on_err), TRUE);
	}
	else if (v->line[v->i] == '>')
	{
		if (v->line[(v->i) + 1] != '>')
			return (add_token(v->p_head, REDIR_TO, ">", v->free_on_err), TRUE);
		return ((v->i)++, add_token(\
v->p_head, APPEND_TO, ">>", v->free_on_err), TRUE);
	}
	else if (v->line[v->i] == '\"' || v->line[v->i] == '\'')
		return (handle_quotes(v, 0), TRUE);
	return (FALSE);
}

static void	tokenizer_vars_init(\
t_tokenizer_vars *v, char *line, t_token **p_head, t_exp_idxs *free_on_err)
{
	v->line = line;
	v->i = 0;
	v->curr_token_val = NULL;
	*p_head = NULL;
	v->p_head = p_head;
	v->free_on_err = free_on_err;
}

/* Do after checks and memory cleanup */
static void	after_checks(t_tokenizer_vars *v)
{
	if (strlen_null(v->curr_token_val) > 0)
		add_token(v->p_head, STRING, v->curr_token_val, v->free_on_err);
	if (v->curr_token_val != NULL)
		free(v->curr_token_val);
}

// TODO: Carry vars into a struct & create an initializer function?
t_token	*tokenize(char *line, t_exp_idxs	*free_on_err)
{
	t_token				*head;
	t_tokenizer_vars	v;

	tokenizer_vars_init(&v, line, &head, free_on_err);
	while (v.line[v.i] != '\0')
	{
		if (!handle_if_first_char(&v))
		{
			str_appendc(&v.curr_token_val, v.line[v.i]);
			if (v.line[v.i + 1] == '\0'
				|| v.line[v.i + 1] == ' ' || v.line[v.i + 1] == '|')
			{
				add_token(&head, STRING, v.curr_token_val, v.free_on_err);
				v.curr_token_val[0] = '\0';
			}
			else if (v.line[v.i + 1] == '>' || v.line[v.i + 1] == '<')
				handle_redirs(&v);
			else if (v.line[v.i + 1] == '\"' || v.line[v.i + 1] == '\'')
				handle_quotes(&v, 1);
		}
		++v.i;
	}
	return (after_checks(&v), head);
}
