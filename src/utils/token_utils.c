/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:49:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/10 15:15:21 by JFikents         ###   ########.fr       */
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

t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		ft_free_link_list(token);
		exit_error("minishell: "E_ALLOC, 1);
	}
	new_token->value = ft_strdup(token->value);
	if (new_token->value == NULL)
	{
		ft_free_n_null((void **)&new_token);
		ft_free_link_list(token);
		exit_error("minishell: "E_ALLOC, 1);
	}
	new_token->type = token->type;
	return (new_token);
}

void	add_token_last(t_token **head, t_token **new)
{
	t_token	*last;
	t_token	*new_token;

	new_token = dup_token(*new);
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_token;
	new_token->prev = last;
}

void	ft_free_link_list(t_token *split)
{
	t_token	*tmp;

	while (split)
	{
		tmp = split;
		split = split->next;
		ft_free_n_null((void **)&tmp->value);
		ft_free_n_null((void **)&tmp);
	}
}
