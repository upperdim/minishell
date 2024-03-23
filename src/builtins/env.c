/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 20:29:08 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char *input)
{
	extern char	**environ;
	int			i;

	while (*input == ' ')
		input++;
	if (*input)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(input, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return ;
	}
	i = 0;
	while (environ[i])
		ft_putendl_fd(environ[i++], 1);
}
