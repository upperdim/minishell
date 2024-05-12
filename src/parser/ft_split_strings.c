/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:54 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/12 13:58:39 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_expand_env_var(char *input, t_split *new, char *end_point)
{
	(void) input;
	(void) new;
	(void) end_point;
	return ;
}

static void	ft_free_split(t_split *split)
{
	t_split	*tmp;

	while (split)
	{
		tmp = split;
		split = split->next;
		ft_free_n_null((void **)&tmp->result);
		ft_free_n_null((void **)&tmp);
	}
}

static int	ft_count_spaces(char *input)
{
	int	index;

	index = 0;
	while (input[index] != ' ')
		index++;
	return (index);
}

static int	ft_check_quotes(char *input, t_split *new)
{
	char	*closing_quote;
	char	*tmp_str;
	char	*prev_result;
	int		index;

	index = ft_count_spaces(input);
	if (input[index] != '\"' || input[index] != '\'')
		return (0);
	closing_quote = ft_strchr(&input[index + 1], input[index]);
	if (!closing_quote)
		return (0);
	prev_result = new->result;
	tmp_str = ft_substr(&input[index], 1, closing_quote - &input[index] - 1);
	new->result = tmp_str;
	if (prev_result)
	{
		new->result = ft_strjoin(prev_result, tmp_str);
		ft_free_n_null((void **)&tmp_str);
		ft_free_n_null((void **)&prev_result);
	}
	if (*closing_quote == '\"')
		ft_expand_env_var(&input[index], new, closing_quote);
	index = closing_quote + 1 - input;
	return (1);
}

static int	ft_start_next_str(char *input, t_split *new)
{
	int	index;

	index = ft_count_spaces(input);
	new->next = ft_calloc(1, sizeof(t_split));
	if (!new->next)
		return (ft_free_split(new), -1);
	new = new->next;
	return (index);
}

static int	ft_check_4_word(char *input, t_split *new)
{
	char	*space;
	char	*tmp_str;
	int		index;
	int		check;

	index = 0;
	/*
	TODO: refactor this function so the while checks for quotes, and I can use
		the return value to advance the pointer
	*/
	while (ft_check_quotes(input, new))
	{
		index += ft_check_quotes(input, new);
		if (input[index] == ' ' && index++)
		{
			check = ft_start_next_str(input, new);
			if (check == -1)
				return ;
			index += check;
		}
	}
	space = ft_strchr(&input[index], ' ');
	if (space == NULL)
		ft_check_quotes(input, new);
	//TODO: check for quotes in the middle of the string
	tmp_str = ft_substr(*input, 0, space - *input);
	if (!tmp_str)
		return (ft_free_split(new), 1);
	if (!new->result)
		new->result = tmp_str;
	else
	{
		new->result = ft_strjoin(new->result, tmp_str);
		ft_free_n_null((void **)&tmp_str);
	}
	if (ft_strchr(*input, '$') < space)
		ft_expand_env_var(input, new, space);
	*input = space + 1;
	if (**input == ' ' && *input++)
		ft_start_next_str(input, new);
	return (index);
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
	}
	return (new);
}
