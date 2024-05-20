/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/20 14:19:18 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_split	*ft_tokenize_pipe(t_split *token)
{
	char	*pipe;
	t_split	*new_tokens;
	// char	**pipe_split;
	// int		pipe_count;

	pipe = ft_strchr(token->result, '|');
	*pipe = '\0';
	new_tokens = ft_calloc(1, sizeof(t_split));
	if (!new_tokens)
		return (NULL);
	// new_tokens->result = ft_substr();
	// pipe_split = ft_split(token->result, '|');
	// pipe_count = 0;
	// while (pipe_split[pipe_count])
	// 	pipe_count ++;
	return token;
}
