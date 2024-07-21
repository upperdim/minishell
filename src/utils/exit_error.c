/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:44:04 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/21 22:41:05 by tunsal           ###   ########.fr       */
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

void	exit_free_idx_arrays(\
char *err_msg, t_list_int *tilda_idxs_to_exp, t_list_int *var_idxs_to_exp)
{
	list_int_free_all(tilda_idxs_to_exp);
	list_int_free_all(var_idxs_to_exp);
	exit_error(err_msg, EXIT_FAILURE);
}

void	exit_free_exp_idxs(\
char *err_msg, t_exp_idxs *exp_idx_pair_to_free)
{
	exit_free_idx_arrays(\
err_msg, exp_idx_pair_to_free->tld_idxs, exp_idx_pair_to_free->var_idxs);
}
