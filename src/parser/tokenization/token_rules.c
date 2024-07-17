/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:17:05 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 12:29:21 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return whether token list obeys rules or not */
int	check_token_rules(t_token *head)
{
	t_token	*iter;
	
	iter = head;
	while (iter != NULL)
	{
		if (iter->type == PIPE && (iter->prev == NULL || iter->next == NULL || \
		iter->next->type != STRING))
			return (FALSE);
		else if (iter->type != STRING\
		&& (iter->next == NULL || iter->next->type != STRING))
			return (FALSE);
		iter = iter->next;
	}
	return (TRUE);
}
