/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:26:52 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/18 22:31:09 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokenize_pipe(t_split *token)
{
	char	*pipe;

	pipe = ft_strchr(token->result, '|');
	ft_printf("prev result: %s\n", token->prev->result);
	return ;
}
