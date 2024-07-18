/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/19 06:30:52 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_quotes(char *line)
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
		return (ft_printf("minishell: SyntaxError: unclosed quotes\n"), NULL);
	tilda_idxs_to_expand = NULL;
	detect_tilda_expansions(line, &tilda_idxs_to_expand);
	var_idxs_to_expand = NULL;
	detect_var_expansions(line, &var_idxs_to_expand, 0);
	token_list = tokenize(line);
	if (!check_token_rules(token_list))
		return (ft_printf("minishell: SyntaxError: invalid tokens\n"), NULL);
	expand_tilda(token_list, tilda_idxs_to_expand, list_get_size(tilda_idxs_to_expand));
	expand_var(token_list, var_idxs_to_expand, list_get_size(var_idxs_to_expand));
	if (!merge_quotes(token_list))
		return (ft_printf("SyntaxError: unclosed quotes\n"), NULL);
	return (token_list);
}
