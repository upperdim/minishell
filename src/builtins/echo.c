/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/25 11:14:27 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_n_flag(char **input)
{
	int		option_n;
	int		i;
	int		arg_num;

	option_n = 0;
	arg_num = 0;
	while (ft_strncmp(input[++arg_num], "-n", 2) == 0)
	{
		i = 2;
		option_n++;
		while (input[arg_num][i] == 'n')
			i++;
		if (input[arg_num][i] != '\0')
			return (option_n - 1);
	}
	return (option_n);
}

int	echo(char **input)
{
	const int	option_n = check_for_n_flag(input);
	int			status;
	int			i;

	i = 0;
	status = 0;
	if (option_n != false)
		i += option_n;
	while (input[++i])
	{
		if (i > 1 + option_n)
			status = ft_printf(" ");
		if (status == -1)
			return (EXIT_FAILURE);
		status = ft_printf(input[i], 1);
		if (status == -1)
			return (EXIT_FAILURE);
	}
	if (option_n == false)
		status = ft_printf("\n", 1);
	if (status == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
