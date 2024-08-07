/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:44:04 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/22 06:55:43 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up(void)
{
	extern char	**environ;

	ft_free_2d_array((void ***)&environ, -1);
	rl_clear_history();
	rl_replace_line("", 1);
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
	ft_putstr_fd("minishell: ", 2);
	perror(NULL);
	exit_error(NULL, exit_status);
}
