/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:00:43 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/20 13:07:31 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// extern char	**environ;
void	ft_expand_env_var(char *input, int index, t_split *new,
	const char *end_point)
{
	(void) input;
	(void) new;
	(void) index;
	(void) end_point;
	return ;
}

void	ft_free_split(t_split *split)
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

int	ft_count_spaces(char *input)
{
	int	index;

	index = 0;
	while (input[index] == ' ')
		index++;
	return (index);
}

int	ft_init_next_token_if_space(char *input, t_split **new)
{
	int	index;

	index = ft_count_spaces(input);
	if (index == 0)
		return (0);
	if (input[index] == '\0')
		return (index);
	(*new)->next = ft_calloc(1, sizeof(t_split));
	if (!(*new)->next)
		return (ft_free_split((*new)), -1);
	(*new)->next->prev = (*new);
	(*new) = (*new)->next;
	return (index);
}

char	*ft_find_limit(char *input)
{
	char	*space;
	char	*single_quote;
	char	*double_quote;
	char	*delimmiter;

	space = ft_strchr(input, ' ');
	single_quote = ft_strchr(input, '\'');
	double_quote = ft_strchr(input, '\"');
	delimmiter = NULL;
	if (space != NULL
		&& (space < single_quote || single_quote == NULL)
		&& (space < double_quote || double_quote == NULL))
		delimmiter = space;
	if (single_quote != NULL
		&& (single_quote < space || space == NULL)
		&& (single_quote < double_quote || double_quote == NULL))
		delimmiter = single_quote;
	if (double_quote != NULL
		&& (double_quote < space || space == NULL)
		&& (double_quote < single_quote || single_quote == NULL))
		delimmiter = double_quote;
	if (delimmiter == NULL)
		delimmiter = input + ft_strlen(input);
	return (delimmiter);
}
