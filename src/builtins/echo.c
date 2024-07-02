/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/02 14:36:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_n_flag(char **input)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	if (ft_strncmp(input[1], "-n", 2) == 0)
	{
		i = 2;
		while (input[1][i++] == 'n')
			flag_n = 1;
		if (input[1][i] != '\0')
			return (0);
	}
	return (flag_n);
}

void	echo(char **input)
{
	int			i;
	const int	flag_n = check_for_n_flag(input);


	i = flag_n;
	while (input[++i])
	{
		if (i > 1 + flag_n)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(input[i], 1);
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}
