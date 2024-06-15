/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:49:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/14 14:40:49 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Isolates a token from the linked list.
 * 
 * @param token the token to isolate
 * @return t_token* the next token after the isolated token or if there is no
 * 	next token, the previous token, or NULL if there is no previous token either.
 */
t_token	*isolate_token(t_token **token)
{
	t_token	*isolated_token;

	isolated_token = *token;
	*token = (*token)->next;
	if (isolated_token->prev)
		isolated_token->prev->next = isolated_token->next;
	isolated_token->prev = NULL;
	if (isolated_token->next)
		isolated_token->next->prev = isolated_token->prev;
	isolated_token->next = NULL;
	return (isolated_token);
}

void	add_token_last(t_token **head, t_token **new)
{
	t_token	*last;
	t_token	*isolated_token;

	isolated_token = isolate_token(new);
	if (*head == NULL)
	{
		*head = isolated_token;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = isolated_token;
	isolated_token->prev = last;
}
