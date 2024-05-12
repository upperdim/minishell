/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:54 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/12 15:06:18 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_quotes(char *input, t_split *new)
{
	char	*closing_quote;
	char	*quoted_str;
	char	*prev_result;
	int		index;

	index = ft_count_spaces(input);
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
	ft_free_n_null((void **)&quoted_str);
	ft_free_n_null((void **)&prev_result);
	if (*closing_quote == '\"' && ft_strchr(quoted_str, '$'))
		ft_expand_env_var(input, index, new, closing_quote);
	return (index = closing_quote + 1 - input);
}

static int	ft_check_4_word(char *input, t_split *new)
{
	char	*delimmiter;
	char	*new_token;
	char	*old_result;
	int		index;
	int		check;

	index = 0;
	delimmiter = ft_find_delimmiter(input);
	while (input[index] == '\"' || input[index] == '\'')
	{
		index += ft_handle_quotes(input, new);
		check = ft_init_next_token_if_space(input, new);
		if (check == -1)
			return (-1);
		index += check;
	}
	old_result = new->result;
	new_token = ft_substr(&input[index], 0, delimmiter - &input[index]);
	if (!new_token)
		return (ft_free_split(new), -1);
	new->result = ft_strjoin(old_result, new_token);
	ft_free_n_null((void **)&new_token);
	ft_free_n_null((void **)&old_result);
	if (ft_strchr(&input[index], '$') < delimmiter)
		ft_expand_env_var(input, index, new, delimmiter);
	return (index + delimmiter - &input[index] + 1);
}

t_split	*ft_split_strings(char *input)
{
	t_split	*new;
	int		index;

	index = 0;
	new = ft_calloc(1, sizeof(t_split));
	if (new == NULL)
		return (NULL);
	while (input != NULL && input[index] != '\0')
	{
		while (input[index] == ' ')
			index++;
		if (!input[index])
			return ;
		index = ft_check_4_word(&input[index], new);
		ft_init_next_token_if_space(input, new);
	}
	return (new);
}
