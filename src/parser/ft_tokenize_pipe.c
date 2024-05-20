/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/20 15:40:25 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*ft_tokenize_pipe(t_split *token)
{
	char		*pipe;
	t_split		*new_tokens;
	const char	*prev_result = token->result;

	pipe = ft_strchr(token->result, '|');
	pipe[0] = '\0';
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
	if (pipe[1] != '\0')
	{
		token->result = new_tokens->result;
		new_tokens->result = ft_strdup(pipe + 1);
		if (!new_tokens->result)
			return (ft_free_n_null((void **)&token->result),
				token->result = (char *)prev_result, NULL);
		token->next = new_tokens->next;
		new_tokens->prev = token;
	}
	else
	{
		ft_free_n_null((void **)&token->result);
		token->result = NULL;
	}
	return (token);
}
