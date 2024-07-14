/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/09 15:17:54 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(const int argc)
{
	extern char	**environ;
	int			i;

	if (argc > 1)
	{
		ft_printf_fd(2, ERROR_MSG, "env", "Too many arguments");
		return (EXIT_FAILURE);
	}
	i = -1;
	while (environ[++i])
		if (ft_strchr(environ[i], '=') != NULL)
			ft_putendl_fd(environ[i], 1);
	return (EXIT_SUCCESS);
}
