/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 00:22:34 by tunsal           ###   ########.fr       */
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

static void	free_expansion_idxs(t_exp_idxs *exp_idxs)
{
	list_int_free_all(exp_idxs->tld_idxs);
	list_int_free_all(exp_idxs->var_idxs);
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
		exit_free_exp_idxs(ERR_MSG_MALLOC, &exp_idxs);
	if (detect_var_exp(line, &exp_idxs.var_idxs, 0, 0) == FAILURE)
		exit_free_exp_idxs(ERR_MSG_MALLOC, &exp_idxs);
	token_list = tokenize(line, &exp_idxs);
	if (!check_token_rules(token_list))
		return (ft_printf_fd(2, ERR_MSG_INVALID_TOKENS), NULL);
	expand_tilda(\
token_list, exp_idxs.tld_idxs, list_get_size(exp_idxs.tld_idxs));
	expand_var(token_list, exp_idxs.var_idxs, list_get_size(exp_idxs.var_idxs));
	if (!merge_quotes(token_list))
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	return (free_expansion_idxs(&exp_idxs), token_list);
}
