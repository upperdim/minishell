/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 18:00:35 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *input)
{
	while (*input == ' ')
		input++;
	if (*input)
		ft_putstr_fd(input, 1);
	ft_putstr_fd("\n", 1);
}
