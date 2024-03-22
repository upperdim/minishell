/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 19:23:27 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *input)
{
	int		space_is_present;

	space_is_present = 0;
	while (*input == ' ')
	{
		input++;
		space_is_present = 1;
	}
	if (*input && space_is_present)
		ft_putstr_fd(input, 1);
	else if (*input)
	{
		ft_putstr_fd("minishell: echo", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": command not found", 2);
	}
	ft_putstr_fd("\n", 1);
}
