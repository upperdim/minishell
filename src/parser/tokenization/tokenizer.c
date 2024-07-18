/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 03:53:39 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/18 20:02:03 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_numeric_redir_token(t_token **p_head, char redir_type,
	int single_or_double, char *curr_token_val)
{
	char	*new_val;
	int		new_type;

	new_type = -1;
	new_val = NULL;
	str_append(&new_val, curr_token_val);
	str_appendc(&new_val, redir_type);
	if (single_or_double == 2)
		str_appendc(&new_val, redir_type);
	if (redir_type == '>')
	{
		if (single_or_double == 1)
			new_type = REDIR_TO;
		else if (single_or_double == 2)
			new_type = APPEND_TO;
	}
	else if (redir_type == '<')
	{
		if (single_or_double == 1)
			new_type = REDIR_FROM;
		else if (single_or_double == 2)
			new_type = HERE_DOC;
	}
	add_token(p_head, new_type, new_val);
	free(new_val);
}

// TODO: Do we need to get a pointer to curr_token_val like the other functions?
// Why does this work while others don't?
static void	handle_redirs(char *line, int *i, char *curr_token_val,
	t_token **p_head)
{
	char	redir_type;

	redir_type = line[*i + 1];
	if (!str_is_numeric(curr_token_val))
	{
		add_token(p_head, STRING, curr_token_val);
		curr_token_val[0] = '\0';
		return ;
	}
	if (ft_atol(curr_token_val) > INT_MAX || ft_atol(curr_token_val) < 0)
	{
		add_token(p_head, STRING, curr_token_val);
		curr_token_val[0] = '\0';
		return ;
	}
	if (line[*i + 2] != '\0' && line[*i + 2] == redir_type)
	{
		add_numeric_redir_token(p_head, redir_type, 2, curr_token_val);
		(*i) += 1;
	}
	else
		add_numeric_redir_token(p_head, redir_type, 1, curr_token_val);
	curr_token_val[0] = '\0';
	(*i)++;
}

/*
	Updates `curr_token_val` and adjusts `i` after properly handling quotes.

	Inputs:
	- line              : input line
	- i                 : current index in the line
	- idx_dist_to_quote : adding this to `i` should give index of the opening quote

	Outputs:
	- curr_token_val : updated current token value
	- i              : updated index position in the line  
*/
static void	handle_quotes(char *line, int *i, int idx_dist_to_quote,
	char **p_curr_token_val, t_token **p_head)
{
	const char	quote_type = line[*i + idx_dist_to_quote];
	const int	next_quote_idx
		= find_idx_of_nextc(line, *i + idx_dist_to_quote + 1, quote_type);

	if (next_quote_idx == -1)
		// Carry here and free every allocation
		exit_error("SyntaxError: unclosed quotes", EXIT_FAILURE);
	else if (next_quote_idx == *i + idx_dist_to_quote + 1)
	{
		if (strlen_null(*p_curr_token_val) == 0)
			add_token(p_head, STRING, "");
		(*i)++;
	}
	else
	{
		str_append_free(p_curr_token_val,
			str_sub(line, *i + idx_dist_to_quote + 1, next_quote_idx - 1));
		(*i) = next_quote_idx;
	}
}

/* These checks shall be true only if it's the first char after a token */
static int	handle_if_first_char(char *line, int *i, char **p_curr_token_val,
	t_token **p_head)
{
	if (line[*i] == ' ')
	{
		if (strlen_null(*p_curr_token_val) > 0)
		{
			add_token(p_head, STRING, *p_curr_token_val);
			*p_curr_token_val[0] = '\0';
		}
		return (TRUE);
	}
	else if (line[*i] == '|')
		return (add_token(p_head, PIPE, "|"), TRUE);
	else if (line[*i] == '<')
	{
		if (line[(*i) + 1] != '<')
			return (add_token(p_head, REDIR_FROM, "<"), TRUE);
		return ((*i)++, add_token(p_head, HERE_DOC, "<<"), TRUE);
	}
	else if (line[*i] == '>')
	{
		if (line[(*i) + 1] != '>')
			return (add_token(p_head, REDIR_TO, ">"), TRUE);
		return ((*i)++, add_token(p_head, APPEND_TO, ">>"), TRUE);
	}
	else if (line[*i] == '\"' || line[*i] == '\'')
		return (handle_quotes(line, i, 0, p_curr_token_val, p_head), TRUE);
	return (FALSE);
}

// TODO: Carry vars into a struct & create an initializer function?
t_token	*tokenize(char *line)
{
	t_token	*head;
	int		i;
	char	*curr_token_val;

	i = 0;
	head = NULL;
	curr_token_val = NULL;
	while (line[i] != '\0')
	{
		if (handle_if_first_char(line, &i, &curr_token_val, &head))
		{
			++i;
			continue ;
		}
		str_appendc(&curr_token_val, line[i]);
		if (line[i + 1] == '\0' || line[i + 1] == ' ' || line[i + 1] == '|')
		{
			add_token(&head, STRING, curr_token_val);
			curr_token_val[0] = '\0';
		}
		else if (line[i + 1] == '>' || line[i + 1] == '<')
			handle_redirs(line, &i, curr_token_val, &head);
		else if (line[i + 1] == '\"' || line[i + 1] == '\'')
			handle_quotes(line, &i, 1, &curr_token_val, &head);
		++i;
	}
	if (strlen_null(curr_token_val) > 0)
		add_token(&head, STRING, curr_token_val);
	if (curr_token_val != NULL)
		free(curr_token_val);
	return (head);
}
