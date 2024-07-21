/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 03:08:46 by tunsal           ###   ########.fr       */
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

t_token	*parse(char *line)
{
	t_token		*token_list;
	t_list_int	*tild_idxs_to_exp;
	t_list_int	*var_idxs_to_exp;

	if (line == NULL || *line == '\0')
		return (NULL);
	token_list = NULL;
	if (validate_quotes(line) == FALSE)
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	tild_idxs_to_exp = NULL;
	var_idxs_to_exp = NULL;
	if (detect_tld_exp(line, ft_strlen(line), &tild_idxs_to_exp) == FAILURE)
		exit_free_idx_arrays(tild_idxs_to_exp, var_idxs_to_exp);
	if (detect_var_exp(line, &var_idxs_to_exp, 0, 0) == FAILURE)
		exit_free_idx_arrays(tild_idxs_to_exp, var_idxs_to_exp);
	token_list = tokenize(line);
	if (!check_token_rules(token_list))
		return (ft_printf_fd(2, ERR_MSG_INVALID_TOKENS), NULL);
	expand_tilda(token_list, tild_idxs_to_exp, list_get_size(tild_idxs_to_exp));
	expand_var(token_list, var_idxs_to_exp, list_get_size(var_idxs_to_exp));
	if (!merge_quotes(token_list))
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	return (token_list);
}
