/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/16 20:33:51 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_line(char *line, t_mallocated *mallocated)
{
	char	*tmp;

	(void)mallocated;
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	else
		return (ft_free_n_null((void **)&line), NULL);
	tmp = ft_strtrim(line, " ");
	if (ft_strlen(tmp) == ft_strlen(line))
		ft_free_n_null((void **)&tmp);
	else
	{
		ft_free_n_null((void **)&line);
		line = tmp;
	}
	return (line);
}
