/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tilda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:26:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 00:04:57 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	search_token_string(\
t_token *cur_tok, t_list_int *tld_idxs_to_exp, int list_size, int *idx_ptrs[2])
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
				&& *p_tld_idx == list_get_val_idx(tld_idxs_to_exp, *p_idx_idx))
			{
				// TODO: carry allocs to here for freeing
				str_replace_section(&cur_tok->value, i, i, getenv("HOME"));
				++(*p_idx_idx);
			}
			++(*p_tld_idx);
		}
		++i;
	}
}

void	expand_tilda(\
t_token *token_list, t_list_int *tilda_idxs_to_expand, const int list_size)
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
			search_token_string(iter, tilda_idxs_to_expand, \
			list_size, ((int *[2]){&idx_idx, &tilda_idx}));
		iter = iter->next;
	}
}
