/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:06:31 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 17:50:23 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	is_valid_var_exp_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

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
void	detect_var_expansions(char *line, t_list_int **p_var_idxs_to_exp, int s)
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
		e = s + 1;
		while (is_valid_var_exp_char(line[e]))
			++e;
		if (e != s + 1)
			list_add(p_var_idxs_to_exp, var_idx);
		else if (line[e] == '$')
		{
			list_add(p_var_idxs_to_exp, var_idx);
			var_idx += 2;
			s += 2;
			continue ;
		}
		s = e;
		++var_idx;
	}
}

static char	*get_msh_pid()
{
	return (ft_itoa(getpid()));
}

static char *get_var_value(char *var_name)
{
	char *result;

	// TODO: Actually get the variable instead of the placeholder
	result = ft_strdup("i_am_");
	str_append(&result, var_name);
	return (result);
}

void	expand_var\
(t_token *token_list, t_list_int *var_idxs_to_expand, const int list_size)
{
	int		var_idx;
	int		idx_idx;
	int		i;
	int		e;
	char	*var_name;
	char	*minish_pid;
	t_token *iter;

	var_idx = 0;
	idx_idx = 0;
	iter = token_list;
	while (iter != NULL)
	{
		if (iter->type == STRING)
		{
			i = 0;
			while (iter->value[i] != '\0')
			{
				if (iter->value[i] == '$')
				{
					if (iter->value[i + 1] == '$')
					{
						minish_pid = get_msh_pid();
						str_replace_section(&iter->value, i, i + 1, minish_pid);
						free(minish_pid);
						++(idx_idx);
						++(var_idx);
					}
					else if (list_size > idx_idx && var_idx == list_get_val_idx(var_idxs_to_expand, idx_idx))
					{
						e = i + 1;
						while (iter->value[e] != '\0' && is_valid_var_exp_char(iter->value[e]))
							++e;
						var_name = str_sub(iter->value, i + 1, e - 1);
						str_replace_section(&iter->value, i, e, get_var_value(var_name));
						free(var_name);
						++(idx_idx);
					}
					++(var_idx);
				}
				++i;
			}
		}
		iter = iter->next;
	}
}
