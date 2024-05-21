/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/21 13:40:31 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_split	*ft_create_new_tokens(t_split *token)
{
	t_split		*new_tokens;

	new_tokens = ft_calloc(1, sizeof(t_split));
	if (!new_tokens)
		return (NULL);
	new_tokens->next = ft_calloc(1, sizeof(t_split));
	if (!new_tokens->next)
		return (ft_free_n_null((void **)&new_tokens), NULL);
	new_tokens->next->prev = new_tokens;
	new_tokens->next->token = PIPE;
	new_tokens->result = ft_strdup(token->result);
	if (!new_tokens->result)
		return (ft_free_n_null((void **)&new_tokens->next),
			ft_free_n_null((void **)&new_tokens), NULL);
	token->prev->next = new_tokens;
	new_tokens->prev = token->prev;
	new_tokens->next->next = token->next;
	return (new_tokens);
}

t_split	*ft_tokenize_pipe(t_split *token)
{
	char		*pipe;
	t_split		*new_tokens;
	const char	*prev_result = token->result;

	pipe = ft_strchr(token->result, '|');
	pipe[0] = '\0';
	new_tokens = ft_create_new_tokens(token);
	if (!new_tokens)
		return (NULL);
	if (pipe[1] != '\0')
	{
		token->result = ft_strdup(pipe + 1);
		if (!token->result)
			return (ft_free_n_null((void *)&token),
				ft_free_n_null((void *)&prev_result), NULL);
		token->token = STRING;
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
