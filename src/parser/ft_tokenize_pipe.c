/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/27 19:45:41 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*ft_separate_to_new_token(t_token *token, const char *limit,
	enum e_token type)
{
	t_token		*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = ft_substr(token->content, 0, limit - token->content);
	if (new_token->content == NULL)
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
	new_token->content = ft_strdup(limit);
	if (new_token->content == NULL)
		return (ft_free_n_null((void **)&new_token), NULL);
	new_token->type = type;
	new_token->prev = token;
	new_token->next = token->next;
	token->next = new_token;
	return (new_token);
}

t_token	*ft_tokenize_pipe(t_token *token)
{
	char *const	old_content = token->content;
	const char	*pipe = ft_strchr(token->content, '|');

	if (pipe == token->content)
		return (token->type = PIPE, token->next);
	token = ft_separate_to_new_token(token, pipe, PIPE);
	if (token == NULL)
		return (ft_free_n_null((void **)&old_content), NULL);
	if (pipe[1] != '\0')
		token = ft_separate_to_new_token(token, token->content + 1, STRING);
	if (token == NULL)
		return (ft_free_n_null((void **)&old_content), NULL);
	return (ft_free_n_null((void **)&old_content), token->next);
}
