/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:07:23 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 00:09:18 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_eligible_for_exp(char *line, int *s, int *in_quote, int *var_idx)
{
	if (line[*s] == '\'')
	{
		*in_quote = !(*in_quote);
		return (++(*s), FALSE);
	}
	if (line[*s] != '$')
		return (++(*s), FALSE);
	if (*in_quote)
	{
		++(*var_idx);
		return (++(*s), FALSE);
	}
	if (ft_isdigit(line[*s + 1]))
	{
		(*s) += 2;
		return (++(*var_idx), FALSE);
	}
	return (TRUE);
}

/*
	`s` was defined here for norm complience.
	It's not a real variable, it initially must always be received as 0.
*/
int	detect_var_expansions(char *line, t_list_int **p_var_idxs_to_exp, int s)
{
	int	var_idx;
	int	e;
	int	is_in_single_quote;

	is_in_single_quote = FALSE;
	var_idx = 0;
	while (line[s] != '\0')
	{
		if (!is_eligible_for_exp(line, &s, &is_in_single_quote, &var_idx))
			continue ;
		if (line[s + 1] == '?')
		{
			if (!list_add(p_var_idxs_to_exp, var_idx))
				return (FAILURE);
			++s;
			continue ;
		}
		e = s + 1;
		while (is_valid_var_exp_char(line[e]))
			++e;
		if (e != s + 1)
		{
			if (!list_add(p_var_idxs_to_exp, var_idx))
				return (FAILURE);
		}
		else if (line[e] == '$')
		{
			if (!list_add(p_var_idxs_to_exp, var_idx))
				return (FAILURE);
			var_idx += 2;
			s += 2;
			continue ;
		}
		s = e;
		++var_idx;
	}
	return (SUCCESS);
}
