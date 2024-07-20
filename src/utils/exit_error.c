/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:44:04 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/19 21:12:29 by tunsal           ###   ########.fr       */
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
	ft_putstr_fd("minishell: ", 2);
	perror(NULL);
	exit_error(NULL, exit_status);
}

void	exit_free_idx_arrays\
(t_list_int *tilda_idxs_to_exp, t_list_int *var_idxs_to_exp)
{
	list_int_free_all(tilda_idxs_to_exp);
	list_int_free_all(var_idxs_to_exp);
	exit_error(ERR_MSG_MALLOC, EXIT_FAILURE);
}
