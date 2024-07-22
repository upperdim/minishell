/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:06:31 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/23 01:57:32 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	If env var was not found and previous token was 
	REDIR_TO, REDIR_FROM or APPEND_TO,
	then you should fail
*/
int	handle_if_should_fail(\
t_token *curr_tok, char *env_var_name, char *env_var_result)
{
	if (curr_tok->prev == NULL)
		return (SUCCESS);
	if (env_var_result != NULL)
		return (SUCCESS);
	if (curr_tok->prev->type == REDIR_TO
		|| curr_tok->prev->type == REDIR_FROM
		|| curr_tok->prev->type == APPEND_TO)
	{
		ft_printf_fd(2, "minishell: $%s: ambiguous redirect\n", env_var_name);
		return (FAILURE);
	}
	return (SUCCESS);
}

// int	handle_if_double_dollar(t_var_exp_vars *v)
// {
// 	char	*minishell_pid;

// 	if (v->iter->value[v->i + 1] == '$')
// 	{
// 		if (!is_prev_here_doc(v->iter))
// 		{
// 			minishell_pid = ft_itoa(getpid());
// 			str_replace_section(&v->iter->value, v->i, v->i + 1, minishell_pid);
// 			free(minishell_pid);
// 			v->tok_val_len = ft_strlen(v->iter->value);
// 		}
// 		++(v->idx_idx);
// 		++(v->var_idx);
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

int	handle_if_double_dollar(t_var_exp_vars *v)
{
	if (v->iter->value[v->i + 1] == '$')
		return (TRUE);
	return (FALSE);
}

int	handle_if_dollar_questionmark(t_var_exp_vars *v)
{
	char	*last_proc_exit_code;

	if (v->iter->value[v->i + 1] == '?')
	{
		if (!is_prev_here_doc(v->iter))
		{
			last_proc_exit_code = getenv("LAST_PROCESS_EXIT_CODE");
			if (handle_if_should_fail(\
			v->iter, "LAST_PROCESS_EXIT_CODE", last_proc_exit_code) == FAILURE)
				return (FAILURE);
			if (str_replace_section(&(v->iter->value), v->i, v->i + 1, last_proc_exit_code) == FAILURE)
				exit_free_toklst_exp_idxs(v->token_list_head, v->exp_idxs, v->line);
			v->tok_val_len = ft_strlen(v->iter->value);
		}
		++(v->idx_idx);
		return (TRUE);
	}
	return (FALSE);
}

void	exit_error_env_var(t_var_exp_vars *v)
{
	if (v->env_var_name != NULL)
		free(v->env_var_name);
	exit_free_toklst_exp_idxs(v->token_list_head, v->exp_idxs, v->line);
}

int	handle_if_will_be_expanded(t_var_exp_vars *v)
{
	if (!(v->list_size > v->idx_idx) 
		|| v->var_idx != list_get_idx(v->exp_idxs->var_idxs, v->idx_idx))
		return (FALSE);
	v->e = v->i + 1;
	while (v->iter->value[v->e] != '\0' && is_valid_var_exp_char(v->iter->value[v->e]))
		++v->e;
	if (!is_prev_here_doc(v->iter))
	{
		v->env_var_name = str_sub(v->iter->value, v->i + 1, v->e - 1);
		if (v->env_var_name == NULL)
			exit_error_env_var(v);
		v->env_var_val = getenv(v->env_var_name);
		if (handle_if_should_fail(v->iter, v->env_var_name, v->env_var_val) == FAILURE)
			return (FAILURE);
		if (str_replace_section(&(v->iter->value), v->i, v->e - 1, v->env_var_val) == FAILURE)
			exit_error_env_var(v);
		free(v->env_var_name);
		v->tok_val_len = ft_strlen(v->iter->value);
	}
	++v->idx_idx;
	return (TRUE);
}

int	handle_if_special_case(t_var_exp_vars *v)
{
	if (!handle_if_double_dollar(v))
	{
		++v->i;
		++v->var_idx;
		return (TRUE);
	}
	v->ret = handle_if_dollar_questionmark(v);
	if (v->ret == FAILURE)
		return (FAILURE);
	else if (v->ret == TRUE)
	{
		++v->i;
		++v->var_idx;
		return (TRUE);
	}
	return (FALSE);
}

static void	var_expansion_vars_init(\
t_var_exp_vars *v, t_token *token_list, t_exp_idxs	*exp_idxs, char *line)
{
	v->var_idx = 0;
	v->idx_idx = 0;
	v->i = 0;
	v->e = 0;
	v->env_var_name = NULL;
	v->env_var_val = NULL;
	v->tok_val_len = 0;
	v->iter = token_list;
	v->token_list_head = token_list;
	v->exp_idxs = exp_idxs;
	v->line = line;
	v->list_size = list_get_size(exp_idxs->var_idxs);
}

int	expand_var(t_token *token_list, t_exp_idxs	*exp_idxs, char *line)
{
	t_var_exp_vars v;

	var_expansion_vars_init(&v, token_list, exp_idxs, line);
	while (v.iter != NULL)
	{
		if (v.iter->type == STRING)
		{
			v.tok_val_len = ft_strlen(v.iter->value);
			v.i = -1;
			while (++(v.i) < v.tok_val_len)
			{
				if (v.iter->value[v.i] == '$')
				{
					v.ret = handle_if_special_case(&v);
					if (v.ret == FAILURE)
						return (FAILURE);
					else if (v.ret == FALSE)
						handle_if_will_be_expanded(&v);
					++v.var_idx;
				}
			}
		}
		v.iter = v.iter->next;
	}
	return (SUCCESS);
}
