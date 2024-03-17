/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 15:08:55 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char *input)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (ft_strnstr(input, "env", 3))
	{
		while (environ[i])
		{
			ft_putstr_fd(environ[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
}
