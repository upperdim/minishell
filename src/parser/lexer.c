/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:29:54 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/27 17:57:49 by JFikents         ###   ########.fr       */
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
		if (new->content == NULL)
			return (-1);
		return (ft_free_n_null((void **)&prev_result), 1);
	}
	new->type = DOUBLE_QUOTES;
	if (input[index] == '\'')
		new->type = SINGLE_QUOTES;
	if (prev_result != NULL)
		new->type = STRING;
	quoted_str = ft_substr(&input[index], 1, closing_quote - &input[index] - 1);
	if (quoted_str == NULL)
		return (-1);
	new->content = ft_strjoin(prev_result, quoted_str);
	if (new->content == NULL)
		return (ft_free_n_null((void **)&quoted_str), -1);
	return (ft_free_n_null((void **)&quoted_str),
		ft_free_n_null((void **)&prev_result), closing_quote + 1 - input);
}

static char	*ft_find_limit(char *input)
{
	char *const	space = ft_strchr(input, ' ');
	char *const	single_quote = ft_strchr(input, '\'');
	char *const	double_quote = ft_strchr(input, '\"');

	if (space != NULL
		&& (space < single_quote || single_quote == NULL)
		&& (space < double_quote || double_quote == NULL))
		return (space);
	if (single_quote != NULL
		&& (single_quote < space || space == NULL)
		&& (single_quote < double_quote || double_quote == NULL))
		return (single_quote);
	if (double_quote != NULL
		&& (double_quote < space || space == NULL)
		&& (double_quote < single_quote || single_quote == NULL))
		return (double_quote);
	return (input + ft_strlen(input));
}

static int	ft_split_to_link_list(char *input, t_token *new)
{
	const int	idx = 0;
	const char	*limiter = ft_find_limit(input);
	char *const	old_token = new->content;
	char		*new_token;

	if (input[idx] == '\"' || input[idx] == '\'')
		return (ft_handle_quotes(&input[idx], new));
	new_token = ft_substr(&input[idx], 0, limiter - &input[idx]);
	if (!new_token)
		return (ft_free_link_list(new), -1);
	if (old_token != NULL && new_token[0] != '\0')
		new->type = STRING;
	new->content = ft_strjoin(old_token, new_token);
	if (new->content == NULL)
		return (ft_free_n_null((void **)&new_token), -1);
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
		else
			check = ft_split_to_link_list(&input[index], current_token);
		if (check == -1)
			return (ft_free_link_list(head), NULL);
		index += check;
	}
	return (head);
}
