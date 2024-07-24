/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:06:31 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/23 02:50:36 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_if_special_case(t_var_exp_vars *v)
{
	if (handle_if_double_dollar(v))
	{
		return (TRUE);
	}
	v->ret = handle_if_dollar_questionmark(v);
	if (v->ret == FAILURE)
		return (FAILURE);
	else if (v->ret == TRUE)
	{
		++v->i;
		++v->var_idx;
		return (TRUE);
	}
	return (FALSE);
}

static int	handle_string(t_var_exp_vars *v)
{
	v->tok_val_len = ft_strlen(v->iter->value);
	v->i = -1;
	while (++(v->i) < v->tok_val_len)
	{
		if (v->iter->value[v->i] == '$')
		{
			v->ret = handle_if_special_case(v);
			if (v->ret == FAILURE)
				return (FAILURE);
			else if (v->ret == FALSE)
			{
				v->ret = handle_if_will_be_expanded(v);
				if (v->ret == FAILURE)
					return (FAILURE);
			}
			++v->var_idx;
		}
	}
	return (SUCCESS);
}

static void	var_expansion_vars_init(\
t_var_exp_vars *v, t_token *token_list, t_exp_idxs	*exp_idxs, char *line)
{
	v->var_idx = 0;
	v->idx_idx = 0;
	v->i = 0;
	v->e = 0;
	v->env_var_name = NULL;
	v->env_var_val = NULL;
	v->tok_val_len = 0;
	v->iter = token_list;
	v->token_list_head = token_list;
	v->exp_idxs = exp_idxs;
	v->line = line;
	v->list_size = list_get_size(exp_idxs->var_idxs);
}

int	expand_var(t_token *token_list, t_exp_idxs	*exp_idxs, char *line)
{
	t_var_exp_vars	v;

	var_expansion_vars_init(&v, token_list, exp_idxs, line);
	while (v.iter != NULL)
	{
		if (v.iter->type == STRING)
		{
			if (handle_string(&v) == FAILURE)
				return (FAILURE);
		}
		v.iter = v.iter->next;
	}
	return (SUCCESS);
}
