/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:06:31 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/18 20:13:30 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_exp_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	is_eligible_for_exp(char *line, int *s, int *in_quote, int *var_idx)
{
	if (line[*s] == '\'')
	{
		*in_quote = !(*in_quote);
		return (++(*s), FALSE);
	}
	if (line[*s] != '$')
		return (++(*s), FALSE);
	if (*in_quote)
	{
		++(*var_idx);
		return (++(*s), FALSE);
	}
	if (ft_isdigit(line[*s + 1]))
	{
		(*s) += 2;
		return (++(*var_idx), FALSE);
	}
	return (TRUE);
}

/*
	`s` was defined here for norm complience.
	It's not a real variable, it initially must always be received as 0.
*/
void	detect_var_expansions(char *line, t_list_int **p_var_idxs_to_exp, int s)
{
	int	var_idx;
	int	e;
	int	is_in_single_quote;

	is_in_single_quote = FALSE;
	var_idx = 0;
	while (line[s] != '\0')
	{
		if (!is_eligible_for_exp(line, &s, &is_in_single_quote, &var_idx))
			continue ;
		if (line[s + 1] == '?')
		{
			list_add(p_var_idxs_to_exp, var_idx);
			++s;
			continue ;
		}
		e = s + 1;
		while (is_valid_var_exp_char(line[e]))
			++e;
		if (e != s + 1)
			list_add(p_var_idxs_to_exp, var_idx);
		else if (line[e] == '$')
		{
			list_add(p_var_idxs_to_exp, var_idx);
			var_idx += 2;
			s += 2;
			continue ;
		}
		s = e;
		++var_idx;
	}
}

void	replace_tok_val_section(t_token *tok, int s, int e, char *replace_with,
	int *p_value_len)
{
	str_replace_section(&tok->value, s, e, replace_with);
	free(replace_with);
	*p_value_len = ft_strlen(tok->value);
}

int	is_prev_here_doc(t_token *tok)
{
	if (tok->prev == NULL)
		return (FALSE);
	if (tok->prev->type == HERE_DOC)
		return (TRUE);
	return (FALSE);
}

/* If env var was not found and previous token was REDIR_TO, REDIR_FROM or
	APPEND_TO; you should fail */
void	handle_if_should_fail(t_token *curr_tok, char *env_var_name,
	char *env_var_result)
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

int	handle_if_double_dollar(t_token *iter, int i, int *p_idx_idx,
	int *p_var_idx, int *p_value_len)
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

int	handle_if_dollar_questionmark(t_token *iter, int i, int *p_idx_idx,
	int *p_value_len)
{
	char	*last_proc_exit_code;

	if (iter->value[i + 1] == '?')
	{
		if (!is_prev_here_doc(iter))
		{
			last_proc_exit_code = getenv("LAST_PROCESS_EXIT_CODE");
			handle_if_should_fail(iter, "LAST_PROCESS_EXIT_CODE",
				last_proc_exit_code);
			str_replace_section(&iter->value, i, i + 1, last_proc_exit_code);
			free(last_proc_exit_code);
			*p_value_len = ft_strlen(iter->value);
		}
		++(*p_idx_idx);
		return (TRUE);
	}
	return (FALSE);
}

void	expand_var(t_token *token_list, t_list_int *var_idxs_to_expand,
	const int list_size)
{
	int		var_idx;
	int		idx_idx;
	int		i;
	int		e;
	char	*var_name;
	char	*env_var_val;
	int		value_len;
	t_token	*iter;

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
							str_replace_section(&iter->value, i, e, env_var_val);
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
