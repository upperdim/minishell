/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_quotes_redirs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 06:11:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 06:11:43 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_numeric_redir_token(\
t_tokenizer_vars *v, char redir_type, int single_or_double)
{
	char	*new_val;
	int		new_type;

	new_type = -1;
	new_val = NULL;
	str_append_tok(&new_val, v->curr_token_val, v);
	str_appendc_tok(&new_val, redir_type, v);
	if (single_or_double == 2)
		str_appendc_tok(&new_val, redir_type, v);
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

void	handle_redirs(t_tokenizer_vars *v)
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
void	handle_quotes(t_tokenizer_vars *v, int idx_dist_to_quot)
{
	char	quote_type;
	int		next_quote_idx;
	char	*sub;

	quote_type = v->line[v->i + idx_dist_to_quot];
	next_quote_idx = str_findc_idx(\
v->line, v->i + idx_dist_to_quot + 1, quote_type);
	if (next_quote_idx == -1)
		exit_free_tokenizer(ERR_MSG_UNCLOSED_QUOTES, v);
	else if (next_quote_idx == v->i + idx_dist_to_quot + 1)
	{
		if (strlen_null(v->curr_token_val) == 0)
			add_token(v->p_head, STRING, "", v->free_on_err);
		(v->i) += idx_dist_to_quot + 2;
	}
	else
	{
		sub = str_sub(v->line, v->i + idx_dist_to_quot, next_quote_idx);
		if (sub == NULL)
			exit_free_tokenizer(ERR_MSG_MALLOC, v);
		str_append_free_tok(&v->curr_token_val, sub, v);
		(v->i) = next_quote_idx;
	}
}
