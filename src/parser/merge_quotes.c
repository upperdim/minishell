/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:34:15 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/18 20:06:40 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Eliminate quote characters from token value */
static void	handle_quotes(char **p_value, int *i)
{
	char	quote_type;
	int		next_quote_idx;
	
	if (*p_value == NULL)
		return ;
	quote_type = (*p_value)[*i];
	next_quote_idx = find_idx_of_nextc(*p_value, *i + 1, quote_type);
	if (next_quote_idx == -1)
		// Carry here and free every allocation
		exit_error("SyntaxError: unclosed quotes", EXIT_FAILURE);
	str_replace_section(p_value, *i, *i, "");
	str_replace_section(p_value, next_quote_idx - 1, next_quote_idx - 1, "");
}

void	merge_quotes(t_token *token_list)
{
	t_token 		*iter;
	int	i;
	
	iter = token_list;
	while (iter != NULL)
	{
		if (iter->type == STRING)
		{
			i = 0;
			while (i < strlen_null(iter->value))
			{
				if (iter->value[i] == '\'' || iter->value[i] == '\"')
					handle_quotes(&iter->value, &i);
				++i;
			}
		}
		iter = iter->next;
	}
}
