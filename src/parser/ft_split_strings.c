/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:54 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/10 18:58:54 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_split(t_split *split)
{
	t_split	*tmp;

	while (split)
	{
		tmp = split;
		split = split->next;
		ft_free_n_null(&tmp->result);
		ft_free_n_null(&tmp);
	}
}

static int	ft_check_quotes(char **input, t_split *new)
{
	char	*closing_quote;
	char	*tmp_str;
	char	*prev_result;

	while (**input == ' ')
		*input++;
	if (*input[0] != '\"' || *input[0] != '\'')
		return (0);
	closing_quote = ft_strchr(*input + 1, **input);
	if (!closing_quote)
		return (0);
	prev_result = new->result;
	tmp_str = ft_substr(*input, 1, closing_quote - *input - 1);
	new->result = tmp_str;
	if (prev_result)
	{
		new->result = ft_strjoin(prev_result, tmp_str);
		ft_free_n_null(&tmp_str);
		ft_free_n_null(&prev_result);
	}
	*input = closing_quote + 1;
	return (1);
}

static int	ft_start_next_str(char **input, t_split *new)
{
	while (**input == ' ')
		*input++;
	new->next = ft_calloc(1, sizeof(t_split));
	if (!new->next)
		return (ft_free_split(new), 1);
	new = new->next;
	return (0);
}

static void	ft_check_4_word(char **input, t_split *new)
{
	char	*space;
	char	*tmp_str;

	while (ft_check_quotes(input, new))
	{
		if (**input == ' ' && *input++)
			if (ft_start_next_str(input, new))
				return ;
	}
	space = ft_strchr(*input, ' ');
	if (!space)
		space = ft_strchr(*input, '\0');
	tmp_str = ft_substr(*input, 0, space - *input);
	if (!tmp_str)
		return (ft_free_split(new), 1);
	if (!new->result)
		new->result = tmp_str;
	else
	{
		new->result = ft_strjoin(new->result, tmp_str);
		ft_free_n_null(&tmp_str);
	}
	*input = space;
}

t_split	*ft_split_strings(char *input)
{
	t_split	*new;

	new = ft_calloc(1, sizeof(t_split));
	if (!new)
		return (NULL);
	while (input && *input)
	{
		while (*input == ' ')
			input++;
		if (!*input)
			return ;
		ft_check_4_word(&input, new);
	}
	return (new);
}
