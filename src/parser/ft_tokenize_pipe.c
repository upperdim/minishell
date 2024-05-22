/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/22 14:13:57 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_create_new_tokens(t_token *token)
{
	t_token		*new_tokens;

	new_tokens = ft_calloc(1, sizeof(t_token));
	if (!new_tokens)
		return (NULL);
	new_tokens->next = ft_calloc(1, sizeof(t_token));
	if (!new_tokens->next)
		return (ft_free_n_null((void **)&new_tokens), NULL);
	new_tokens->next->prev = new_tokens;
	new_tokens->next->type = PIPE;
	new_tokens->content = ft_strdup(token->content);
	if (!new_tokens->content)
		return (ft_free_n_null((void **)&new_tokens->next),
			ft_free_n_null((void **)&new_tokens), NULL);
	token->prev->next = new_tokens;
	new_tokens->prev = token->prev;
	new_tokens->next->next = token->next;
	return (new_tokens);
}

t_token	*ft_tokenize_pipe(t_token *token)
{
	char		*pipe;
	t_token		*new_tokens;
	const char	*prev_result = token->content;

	pipe = ft_strchr(token->content, '|');
	pipe[0] = '\0';
	new_tokens = ft_create_new_tokens(token);
	if (!new_tokens)
		return (NULL);
	if (pipe[1] != '\0')
	{
		token->content = ft_strdup(pipe + 1);
		if (!token->content)
			return (ft_free_n_null((void *)&token),
				ft_free_n_null((void *)&prev_result), NULL);
		token->type = STRING;
		token->next = new_tokens->next->next;
		new_tokens->next->next->prev = token;
		token->prev = new_tokens->next;
		new_tokens->next->next = token;
	}
	else
		ft_free_n_null((void **)&token);
	ft_free_n_null((void **)&prev_result);
	return (new_tokens);
}
