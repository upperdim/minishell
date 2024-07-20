/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:06:31 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 00:10:22 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
	If env var was not found and previous token was 
	REDIR_TO, REDIR_FROM or APPEND_TO,
	then you should fail
*/
void	handle_if_should_fail(\
t_token *curr_tok, char *env_var_name, char *env_var_result)
{
	if (curr_tok->prev == NULL)
		return ;
	if (env_var_result != NULL)
		return ;
	if (curr_tok->prev->type == REDIR_TO
		|| curr_tok->prev->type == REDIR_FROM
		|| curr_tok->prev->type == APPEND_TO)
	{
		// TODO: freeing stuff
		ft_putstr_fd("minishell: $", 2);
		ft_putstr_fd(env_var_name, 2);
		exit_error(": ambiguous redirect", EXIT_FAILURE);
	}
}

int	handle_if_double_dollar(\
t_token *iter, int i, int *p_idx_idx, int *p_var_idx, int *p_value_len)
{
	char	*minishell_pid;

	if (iter->value[i + 1] == '$')
	{
		if (!is_prev_here_doc(iter))
		{
			minishell_pid = ft_itoa(getpid());
			str_replace_section(&iter->value, i, i + 1, minishell_pid);
			free(minishell_pid);
			*p_value_len = ft_strlen(iter->value);
		}
		++(*p_idx_idx);
		++(*p_var_idx);
		return (TRUE);
	}
	return (FALSE);
}

int	handle_if_dollar_questionmark(\
t_token *iter, int i, int *p_idx_idx, int *p_value_len)
{
	char	*last_proc_exit_code;

	if (iter->value[i + 1] == '?')
	{
		if (!is_prev_here_doc(iter))
		{
			last_proc_exit_code = getenv("LAST_PROCESS_EXIT_CODE");
			handle_if_should_fail(\
			iter, "LAST_PROCESS_EXIT_CODE", last_proc_exit_code);
			str_replace_section(&iter->value, i, i + 1, last_proc_exit_code);
			*p_value_len = ft_strlen(iter->value);
		}
		++(*p_idx_idx);
		return (TRUE);
	}
	return (FALSE);
}

void	expand_var(\
t_token *token_list, t_list_int *var_idxs_to_expand, const int list_size)
{
	int		var_idx;
	int		idx_idx;
	int		i;
	int		e;
	char	*var_name;
	char	*env_var_val;
	int		value_len;
	t_token *iter;

	var_idx = 0;
	idx_idx = 0;
	iter = token_list;
	while (iter != NULL)
	{
		if (iter->type == STRING)
		{
			value_len = ft_strlen(iter->value);
			i = 0;
			while (i < value_len)
			{
				if (iter->value[i] == '$')
				{
					if (handle_if_double_dollar(iter, i, &idx_idx, &var_idx, &value_len))
						;
					else if (handle_if_dollar_questionmark(iter, i, &idx_idx, &value_len))
						;
					else if (list_size > idx_idx && var_idx == list_get_val_idx(var_idxs_to_expand, idx_idx))
					{
						e = i + 1;
						while (iter->value[e] != '\0' && is_valid_var_exp_char(iter->value[e]))
							++e;
						if (!is_prev_here_doc(iter))
						{
							var_name = str_sub(iter->value, i + 1, e - 1);
							env_var_val = getenv(var_name);
							handle_if_should_fail(iter, var_name, env_var_val);
							// Sussy wussy (removed -1)
							// str_replace_section(&iter->value, i, e - 1, env_var_val);
							str_replace_section(&iter->value, i, e - 1, env_var_val);
							free(var_name);
							value_len = ft_strlen(iter->value);
						}
						++idx_idx;
					}
					++var_idx;
				}
				++i;
			}
		}
		iter = iter->next;
	}
}
