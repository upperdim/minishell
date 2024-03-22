/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/22 17:53:19 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_line(char *input, t_alloc_list *to_free)
{
	char	*tmp;

	if (!input)
		return (NULL);
	if (*input)
		add_history(input);
	else
		return (ft_free_n_null((void **)&input), NULL);
	tmp = ft_strtrim(input, " ");
	if (ft_strlen(tmp) == ft_strlen(input))
		ft_free_n_null((void **)&tmp);
	else
	{
		ft_free_n_null((void **)&input);
		input = tmp;
	}
	add_to_list(input, INPUT, to_free);
	return (input);
}
