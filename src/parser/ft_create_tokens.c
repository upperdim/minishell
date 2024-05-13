/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:54 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/13 21:42:12 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_quotes(char *input, t_split *new)
{
	char	*closing_quote;
	char	*quoted_str;
	char	*prev_result;
	int		index;

	index = 0;
	closing_quote = ft_strchr(&input[index + 1], input[index]);
	prev_result = new->result;
	if (closing_quote == NULL)
	{
		if (input[index] == '\'')
			new->result = ft_strjoin(prev_result, "\'");
		else
			new->result = ft_strjoin(prev_result, "\"");
		return (ft_free_n_null((void **)&prev_result), 1);
	}
	quoted_str = ft_substr(&input[index], 1, closing_quote - &input[index] - 1);
	new->result = ft_strjoin(prev_result, quoted_str);
	if (*closing_quote == '\"' && ft_strchr(quoted_str, '$'))
		ft_expand_env_var(input, index, new, closing_quote);
	ft_free_n_null((void **)&quoted_str);
	ft_free_n_null((void **)&prev_result);
	return (index = closing_quote + 1 - input);
}

static int	ft_check_4_word(char *input, t_split *new)
{
	char	*limiter;
	char	*new_token;
	char	*old_token;
	int		idx;
	int		check;

	idx = 0;
	while (input[idx] == '\"' || input[idx] == '\'')
	{
		idx += ft_handle_quotes(input, new);
		check = ft_init_next_token_if_space(&input[idx], &new);
		if (check == -1)
			return (-1);
		idx += check;
	}
	limiter = ft_find_limit(&input[idx]);
	old_token = new->result;
	new_token = ft_substr(&input[idx], 0, limiter - &input[idx]);
	if (!new_token)
		return (ft_free_split(new), -1);
	new->result = ft_strjoin(old_token, new_token);
	if (ft_strchr(&input[idx], '$') && ft_strchr(&input[idx], '$') < limiter)
		ft_expand_env_var(input, idx, new, limiter);
	return (ft_free_n_null((void **)&old_token),
		ft_free_n_null((void **)&new_token), idx + limiter - &input[idx]);
}

t_split	*ft_create_tokens(char *input)
{
	t_split	*working_split;
	t_split	*all_tokens;
	int		index;

	index = 0;
	working_split = ft_calloc(1, sizeof(t_split));
	if (working_split == NULL)
		return (NULL);
	all_tokens = working_split;
	while (input != NULL && input[index] != '\0')
	{
		index += ft_init_next_token_if_space(&input[index], &working_split);
		if (!input[index])
			break ;
		index += ft_check_4_word(&input[index], working_split);
	}
	return (all_tokens);
}
