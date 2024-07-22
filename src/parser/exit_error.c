/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 06:55:35 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 06:57:28 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exit_free_toklst_exp_idxs(t_token *tok_lst, t_exp_idxs *exp_idxs)
{
	ft_free_link_list(tok_lst);
	exit_free_exp_idxs(ERR_MSG_MALLOC, exp_idxs);
}
