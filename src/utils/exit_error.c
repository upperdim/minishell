/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 17:44:04 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/22 05:47:07 by tunsal           ###   ########.fr       */
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

void	exit_free_exp_idxs(char *err_msg, t_exp_idxs *exp_idxs)
{
	list_int_free_all(exp_idxs->tld_idxs);
	list_int_free_all(exp_idxs->var_idxs);
	exit_error(err_msg, EXIT_FAILURE);
}

/* Free token list, tilda index list, and variable index list before exiting */
void	exit_free_tokenizer(char *err_msg, t_tokenizer_vars *v)
{
	ft_free_link_list(*v->p_head);
	exit_free_exp_idxs(err_msg, v->free_on_err);
}
