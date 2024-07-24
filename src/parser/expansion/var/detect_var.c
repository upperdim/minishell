/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:07:23 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/24 19:17:41 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_eligible_for_exp(t_detect_var_exp_vars *v)
{
	if (v->line[v->s] == '\'')
	{
		v->in_single_quote = !(v->in_single_quote);
		return (v->s++, FALSE);
	}
	if (v->line[v->s] == '\"')
	{
		v->in_double_quote = !(v->in_double_quote);
		return (v->s++, FALSE);
	}
	if (v->line[v->s] != '$')
		return (v->s++, FALSE);
	if (!v->in_double_quote && v->in_single_quote)
	{
		v->var_idx++;
		return (v->s++, FALSE);
	}
	if (ft_isdigit(v->line[v->s + 1]))
	{
		(v->s) += 2;
		return (v->var_idx++, FALSE);
	}
	return (TRUE);
}

/*
static int	handle_if_special_case(
char *line, int *p_s, int *p_var_idx, t_list_int **p_var_idxs_to_exp)
{
	if (line[(*p_s) + 1] == '?')
	{
		if (list_add(p_var_idxs_to_exp, *p_var_idx) == FAILURE)
			return (FAILURE);
		++(*p_s);
		return (TRUE);
	}
	else if (line[(*p_s) + 1] == '$')
	{
		if (list_add(p_var_idxs_to_exp, *p_var_idx) == FAILURE)
			return (FAILURE);
		*p_var_idx += 2;
		(*p_s) += 2;
		return (TRUE);
	}
	return (FALSE);
}
*/

static int	handle_if_special_case(t_detect_var_exp_vars *v)
{
	if (v->line[v->s + 1] == '?')
	{
		if (list_add(v->p_var_idxs, v->var_idx) == FAILURE)
			return (FAILURE);
		v->s++;
		return (TRUE);
	}
	else if (v->line[v->s + 1] == '$')
	{
		v->var_idx++;
		v->s++;
		return (TRUE);
	}
	return (FALSE);
}

static void	init_vars(\
t_detect_var_exp_vars *v, char *line, t_list_int **p_var_idxs)
{
	v->line = line;
	v->p_var_idxs = p_var_idxs;
	v->s = 0;
	v->e = 0;
	v->var_idx = 0;
	v->in_single_quote = FALSE;
	v->in_double_quote = FALSE;
	v->ret = 0;
}

int	detect_var_exp(char *line, t_list_int **p_var_idxs_to_exp)
{
	t_detect_var_exp_vars	v;

	init_vars(&v, line, p_var_idxs_to_exp);
	while (v.line[v.s] != '\0')
	{
		if (!is_eligible_for_exp(&v))
			continue ;
		v.ret = handle_if_special_case(&v);
		if (v.ret == FAILURE)
			return (FAILURE);
		else if (v.ret == TRUE)
			continue ;
		v.e = v.s + 1;
		while (is_valid_var_exp_char(v.line[v.e]))
			v.e++;
		if (v.e != v.s + 1)
			if (list_add(v.p_var_idxs, v.var_idx) == FAILURE)
				return (FAILURE);
		v.s = v.e;
		v.var_idx++;
	}
	return (SUCCESS);
}
