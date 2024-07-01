/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/01 16:48:13 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **input)
{
	extern char	**environ;
	int			i;

	if (input[1])
	{
		ft_printf_fd(2, "minishell: env: Too many arguments\n");
		return ;
	}
	i = 0;
	while (environ[i])
		ft_putendl_fd(environ[i++], 1);
}
