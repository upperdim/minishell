/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:54 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/26 14:27:55 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_quotes(char *input, t_token *new)
{
	const int	index = 0;
	const char	*prev_result = new->content;
	const char	*closing_quote = ft_strchr(&input[index + 1], input[index]);
	char		*quoted_str;

	if (closing_quote == NULL)
	{
		if (input[index] == '\'')
			new->content = ft_strjoin(prev_result, "\'");
		else
			new->content = ft_strjoin(prev_result, "\"");
		return (ft_free_n_null((void **)&prev_result), 1);
	}
	new->type = DOUBLE_QUOTES;
	if (input[index] == '\'')
		new->type = SINGLE_QUOTES;
	quoted_str = ft_substr(&input[index], 1, closing_quote - &input[index] - 1);
	new->content = ft_strjoin(prev_result, quoted_str);
	return (ft_free_n_null((void **)&quoted_str),
		ft_free_n_null((void **)&prev_result), closing_quote + 1 - input);
}

static char	*ft_find_limit(char *input)
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

static int	ft_split_to_link_list(char *input, t_token *new)
{
	char	*limiter;
	char	*new_token;
	char	*old_token;
	int		idx;
	int		check;

	idx = 0;
	check = 0;
	while (input[idx] != '\0' && (input[idx] == '\"' || input[idx] == '\''))
	{
		idx += ft_handle_quotes(&input[idx], new);
		if (input[idx] == ' ')
			check = ft_move_to_next(&input[idx], &new);
		if (check == -1)
			return (-1);
		idx += check;
	}
	limiter = ft_find_limit(&input[idx]);
	old_token = new->content;
	new_token = ft_substr(&input[idx], 0, limiter - &input[idx]);
	if (!new_token)
		return (ft_free_link_list(new), -1);
	new->content = ft_strjoin(old_token, new_token);
	return (ft_free_n_null((void **)&old_token),
		ft_free_n_null((void **)&new_token), idx + limiter - &input[idx]);
}

t_token	*ft_lexer(char *input)
{
	t_token	*current_token;
	t_token	*head;
	int		index;
	int		check;

	index = 0;
	head = ft_calloc(1, sizeof(t_token));
	if (head == NULL)
		return (NULL);
	current_token = head;
	while (input != NULL && input[index] != '\0')
	{
		check = 0;
		while (current_token->next != NULL)
			current_token = current_token->next;
		if (input[index] == ' ')
			check = ft_move_to_next(&input[index], &current_token);
		if (check == -1)
			return (ft_free_link_list(head), NULL);
		index += check;
		if (!input[index])
			break ;
		index += ft_split_to_link_list(&input[index], current_token);
	}
	return (head);
}
