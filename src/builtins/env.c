/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/02 15:32:34 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(const int argc)
{
	extern char	**environ;
	int			i;

	if (argc > 1)
	{
		ft_printf_fd(2, "minishell: env: Too many arguments\n");
		return ;
	}
	i = -1;
	while (environ[++i])
		if (ft_strchr(environ[i], '=') != NULL)
			ft_putendl_fd(environ[i], 1);
}
