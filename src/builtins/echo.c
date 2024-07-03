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
	int	option_n;

	option_n = 0;
	if (ft_strncmp(input[1], "-n", 2) == 0)
	{
		i = 2;
		while (input[1][i++] == 'n')
			option_n = 1;
		if (input[1][i] != '\0')
			return (0);
	}
	return (option_n);
}

void	echo(char **input)
{
	const int	option_n = check_for_n_flag(input);
	int			i;

	i = 0;
	if (option_n == true)
		i = 1;
	while (input[++i])
	{
		if (i > 1 + option_n)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(input[i], 1);
	}
	if (option_n == false)
		ft_putstr_fd("\n", 1);
}
