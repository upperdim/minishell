/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:07:23 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 03:08:24 by tunsal           ###   ########.fr       */
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

static int	handle_if_special_case(\
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

/*
	`s` was defined here for norm complience.
	It's not a real variable, it initially must always be received as 0.
*/
int	detect_var_exp(\
char *line, t_list_int **p_var_idxs_to_exp, int s, int var_idx)
{
	int	e;
	int	is_in_single_quote;
	int	ret;

	is_in_single_quote = FALSE;
	while (line[s] != '\0')
	{
		if (!is_eligible_for_exp(line, &s, &is_in_single_quote, &var_idx))
			continue ;
		ret = handle_if_special_case(line, &s, &var_idx, p_var_idxs_to_exp);
		if (ret == FAILURE)
			return (FAILURE);
		else if (ret == TRUE)
			continue ;
		e = s + 1;
		while (is_valid_var_exp_char(line[e]))
			++e;
		if (e != s + 1)
			if (list_add(p_var_idxs_to_exp, var_idx) == FAILURE)
				return (FAILURE);
		s = e;
		++var_idx;
	}
	return (SUCCESS);
}
