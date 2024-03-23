/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/23 16:42:36 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *input)
{
	int	status;

	status = 0;
	if (*input == ' ')
		input++;
	if (*input)
		status = chdir(input);
	else
		status = chdir(getenv("HOME"));
	if (status == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
	}
}
