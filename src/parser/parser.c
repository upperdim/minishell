/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 20:27:51 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_quotes(char *line)
{
	char	quote_type;
	int		len;
	int		i;

	quote_type = NOT_QUOTE;
	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (quote_type == NOT_QUOTE && (line[i] == '\'' || line[i] == '\"'))
			quote_type = line[i];
		else if (quote_type == line[i])
			quote_type = NOT_QUOTE;
		++i;
	}
	return (quote_type == NOT_QUOTE);
}

static void	parser_cleanup(t_exp_idxs *exp_idxs)
{
	list_int_free_all(exp_idxs->tld_idxs);
	list_int_free_all(exp_idxs->var_idxs);
}

static void	free_tok_lst_exp_idxs(\
t_token *token_list, t_exp_idxs *exp_idxs)
{
	ft_free_link_list(token_list);
	parser_cleanup(exp_idxs);
}

t_token	*parse(char *line)
{
	t_token		*token_list;
	t_exp_idxs	exp_idxs;

	if (line == NULL || *line == '\0')
		return (NULL);
	token_list = NULL;
	if (validate_quotes(line) == FALSE)
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	exp_idxs.tld_idxs = NULL;
	exp_idxs.var_idxs = NULL;
	if (detect_tld_exp(line, ft_strlen(line), &exp_idxs.tld_idxs) == FAILURE)
		exit_free_exp_idxs(ERR_MSG_MALLOC, &exp_idxs, line);
	if (detect_var_exp(line, &exp_idxs.var_idxs, 0, 0) == FAILURE)
		exit_free_exp_idxs(ERR_MSG_MALLOC, &exp_idxs, line);
	token_list = tokenize(line, &exp_idxs);
	if (!check_token_rules(token_list))
		return (free_tok_lst_exp_idxs(token_list, &exp_idxs), \
ft_printf_fd(2, ERR_MSG_INVALID_TOKENS), NULL);
	expand_tilda(token_list, &exp_idxs, line);
	expand_var(token_list, &exp_idxs);
	if (!merge_quotes(token_list, &exp_idxs, line))
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	return (parser_cleanup(&exp_idxs), token_list);
}
