// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   tokenizer.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/16 03:53:39 by tunsal            #+#    #+#             */
// /*   Updated: 2024/07/17 07:33:35 by tunsal           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// /*
// 	Updates `curr_token_val` and adjusts `i` after properly handling quotes.

// 	Inputs:
// 	- line              : input line
// 	- i                 : current index in the line
// 	- idx_dist_to_quote : adding this to `i` should give index of the opening quote

// 	Outputs:
// 	- curr_token_val : updated current token value
// 	- i              : updated index position in the line  
// */
// void	handle_quotes(char *line, int *i, int idx_dist_to_quote, char *curr_token_val, t_token **p_head)
// {
// 	const char	quote_type = line[*i + idx_dist_to_quote];
// 	const int	next_quote_idx = find_idx_of_nextc(line, *i + idx_dist_to_quote, quote_type);

// 	if (next_quote_idx == -1)
// 		// Carry here and free every allocation
// 		exit_error("SyntaxError: unclosed quotes", EXIT_FAILURE);
// 	else if (next_quote_idx == *i + idx_dist_to_quote + 1)
// 	{
// 		if (strlen_null(curr_token_val) == 0)
// 			add_token(p_head, STRING, "");
// 		(*i)++;
// 	}
// 	else
// 	{
// 		str_append_free(&curr_token_val, str_sub(line, *i + idx_dist_to_quote + 1, next_quote_idx - 1));
// 		(*i)++;
// 	}
// }

// /* These checks shall be true only if it's the first char after a token */
// int	handle_if_first_char(char *line, int *i, char *curr_token_val, t_token **p_head)
// {
// 	if (line[*i] == ' ')
// 	{
// 		if (strlen_null(curr_token_val) > 0)
// 		{
// 			add_token(p_head, STRING, curr_token_val);
// 			curr_token_val[0] = '\0';
// 		}
// 		return (TRUE);
// 	}
// 	else if (line[*i] == '|')
// 		return (add_token(p_head, PIPE, "|"), TRUE);
// 	else if (line[*i] == '<')
// 	{
// 		if (line[(*i) + 1] != '<')
// 			return (add_token(p_head, REDIR_FROM, "<"), TRUE);
// 		return ((*i)++, add_token(p_head, HERE_DOC, "<<"), TRUE);
// 	}
// 	else if (line[*i] == '>')
// 	{
// 		if (line[(*i) + 1] != '>')
// 			return (add_token(p_head, REDIR_TO, ">"), TRUE);
// 		return ((*i)++, add_token(p_head, APPEND_TO, ">>"), TRUE);
// 	}
// 	else if (line[*i] == '\"' || line[*i] == '\'')
// 		return (handle_quotes(line, i, 0, curr_token_val, p_head), TRUE);
// 	return (FALSE);
// }

// t_token	*tokenizer(char *line)
// {
// 	t_token	*head;
// 	int		i;
// 	char	*curr_token_val;
// 	char	redir_type;

// 	// TODO: Carry vars into a struct & create an initializer function?
// 	i = 0;
// 	head = NULL;
// 	curr_token_val = NULL;
// 	while (line[i] != '\0')
// 	{
// 		if (handle_if_first_char(line, &i, curr_token_val, &head))
// 		{
// 			++i;
// 			continue ;
// 		}
		
// 		str_appendc(&curr_token_val, line[i]);
		
// 		if (line[i + 1] == '\0' || line[i + 1] == ' ' || line[i + 1] == '|')
// 		{
// 			add_token(&head, STRING, curr_token_val);
// 			curr_token_val[0] = '\0';
// 		}
// 		else if (line[i + 1] == '>' || line[i + 1] == '<')
// 			redir_type = line[i + 1];

// 		++i;
// 	}
// 	return (head);
// }
