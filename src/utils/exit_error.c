/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:44:04 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/01 15:40:41 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(void)
{
	extern char	**environ;

	ft_free_2d_array((void ***)&environ, -1);
}

void	exit_error(char *error_msg, int exit_status)
{
	if (error_msg)
		ft_putstr_fd(error_msg, 2);
	clean_up();
	exit(exit_status);
}

void	exit_perror(int exit_status)
{
	perror(NULL);
	exit_error(NULL, exit_status);
}
