/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/29 19:23:43 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_separate_to_new_token(t_token *token, const char *limit,
	enum e_token_type type)
{
	t_token		*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = ft_substr(token->value, 0, limit - token->value);
	if (new_token->value == NULL)
		return (ft_free_n_null((void **)&new_token), NULL);
	new_token->type = token->type;
	new_token->prev = token->prev;
	new_token->next = token->next;
	new_token->prev->next = new_token;
	ft_free_n_null((void **)&token);
	token = new_token;
	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->value = ft_strdup(limit);
	if (new_token->value == NULL)
		return (ft_free_n_null((void **)&new_token), NULL);
	new_token->type = type;
	new_token->prev = token;
	new_token->next = token->next;
	token->next = new_token;
	return (new_token);
}

t_token	*ft_tokenize_pipe(t_token *token)
{
	char *const	old_content = token->value;
	const char	*pipe = ft_strchr(token->value, '|');

	if (pipe == token->value)
		return (token->type = PIPE, token->next);
	token = ft_separate_to_new_token(token, pipe, PIPE);
	if (token == NULL)
		return (ft_free_n_null((void **)&old_content), NULL);
	if (pipe[1] != '\0')
		token = ft_separate_to_new_token(token, token->value + 1, STRING);
	if (token == NULL)
		return (ft_free_n_null((void **)&old_content), NULL);
	return (ft_free_n_null((void **)&old_content), token->next);
}
