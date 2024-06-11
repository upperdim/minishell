/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:49:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/11 20:49:22 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	isolate_token(t_token *token)
{
	if (token->prev)
		token->prev->next = token->next;
	token->prev = NULL;
	if (token->next)
		token->next->prev = token->prev;
	token->next = NULL;
}

void	add_token_last(t_token **head, t_token *new)
{
	t_token	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	isolate_token(new);
	last->next = new;
	new->prev = last;
}
