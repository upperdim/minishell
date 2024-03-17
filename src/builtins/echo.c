/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 15:05:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *input)
{
	if (ft_strnstr(input, "echo ", 5))
	{
		ft_putstr_fd(input + 5, 1);
		ft_putstr_fd("\n", 1);
	}
}
