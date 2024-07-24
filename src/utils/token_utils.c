/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:49:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/24 16:32:14 by JFikents         ###   ########.fr       */
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
		free_tokens(token);
		return (ft_printf_fd(2, "minishell: %s\n", E_ALLOC), NULL);
	}
	if (token->value != NULL)
		new_token->value = ft_strdup(token->value);
	if (new_token->value == NULL && token->value != NULL)
	{
		ft_free_n_null((void **)&new_token);
		free_tokens(token);
		return (ft_printf_fd(2, "minishell: %s\n", E_ALLOC), NULL);
	}
	new_token->type = token->type;
	return (new_token);
}

/* Get a pointer to the last element of the token list */
t_token	*token_list_get_last(t_token *list)
{
	t_token	*iter;

	if (list == NULL)
		return (NULL);
	iter = list;
	while (iter->next != NULL)
		iter = iter->next;
	return (iter);
}

void	free_tokens(t_token *split)
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
