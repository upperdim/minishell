/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:17:05 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/18 20:03:04 by JFikents         ###   ########.fr       */
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
		else if (iter->type != STRING
			&& (iter->next == NULL || iter->next->type != STRING))
			return (FALSE);
		iter = iter->next;
	}
	return (TRUE);
}
