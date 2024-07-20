/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/19 20:37:48 by tunsal           ###   ########.fr       */
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

// void	init_parser_vars(t_pvars *pvars, char *line)
// {
// 	pvars->line = line;
// 	pvars->len = ft_strlen(line);
// 	pvars->head = NULL;
// }

t_token	*parse(char *line)
{
	t_token		*token_list;
	t_list_int	*tilda_idxs_to_expand;
	t_list_int	*var_idxs_to_expand;

	if (line == NULL || *line == '\0')
		return (NULL);
	token_list = NULL;
	if (validate_quotes(line) == FALSE)
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	tilda_idxs_to_expand = NULL;
	var_idxs_to_expand = NULL;
	if (!detect_tilda_expansions(line, ft_strlen(line), &tilda_idxs_to_expand))
		exit_free_idx_arrays(tilda_idxs_to_expand, var_idxs_to_expand);
	if (!detect_var_expansions(line, &var_idxs_to_expand, 0))
		exit_free_idx_arrays(tilda_idxs_to_expand, var_idxs_to_expand);
	token_list = tokenize(line);
	if (!check_token_rules(token_list))
		return (ft_printf_fd(2, ERR_MSG_INVALID_TOKENS), NULL);
	expand_tilda(token_list, tilda_idxs_to_expand, list_get_size(tilda_idxs_to_expand));
	expand_var(token_list, var_idxs_to_expand, list_get_size(var_idxs_to_expand));
	if (!merge_quotes(token_list))
		return (ft_printf_fd(2, ERR_MSG_UNCLOSED_QUOTES), NULL);
	return (token_list);
}
