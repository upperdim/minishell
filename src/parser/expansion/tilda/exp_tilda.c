/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tilda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:26:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 07:05:43 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_token_string(\
t_token *cur_tok, t_exp_idxs *exp_idxs, int list_size, int *idx_ptrs[2])
{
	int		*p_idx_idx;
	int		*p_tld_idx;
	int		i;

	p_idx_idx = idx_ptrs[0];
	p_tld_idx = idx_ptrs[1];
	i = 0;
	while (cur_tok->value[i] != '\0')
	{
		if (cur_tok->value[i] == '~')
		{
			if (list_size > *p_idx_idx
				&& *p_tld_idx == list_get_idx(exp_idxs->tld_idxs, *p_idx_idx))
			{
				if (str_replace_section(\
&cur_tok->value, i, i, getenv("HOME")) == FAILURE)
					return (FAILURE);
				++(*p_idx_idx);
			}
			++(*p_tld_idx);
		}
		++i;
	}
	return (SUCCESS);
}

void	expand_tilda(\
t_token *token_list, t_exp_idxs	*exp_idxs, const int list_size)
{
	int		tilda_idx;
	int		idx_idx;
	t_token	*iter;

	tilda_idx = 0;
	idx_idx = 0;
	iter = token_list;
	while (iter != NULL)
	{
		if (iter->type == STRING)
			if (search_token_string(\
iter, exp_idxs, list_size, ((int *[2]){&idx_idx, &tilda_idx})) == FAILURE)
				exit_free_toklst_exp_idxs(token_list, exp_idxs);
		iter = iter->next;
	}
}
