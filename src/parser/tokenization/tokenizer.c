/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:53:39 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 06:10:44 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			str_appendc_tok(&v.curr_token_val, v.line[v.i], &v);
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
