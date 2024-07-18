/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/18 20:11:43 by JFikents         ###   ########.fr       */
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
		exit_error("minishell: SyntaxError: unclosed quotes", EXIT_FAILURE);
	tilda_idxs_to_expand = NULL;
	detect_tilda_expansions(line, &tilda_idxs_to_expand);
	var_idxs_to_expand = NULL;
	detect_var_expansions(line, &var_idxs_to_expand, 0);
	token_list = tokenize(line);
	if (!check_token_rules(token_list))
		exit_error("minishell: SyntaxError: invalid tokens", EXIT_FAILURE);
	expand_tilda(token_list, tilda_idxs_to_expand, list_get_size(tilda_idxs_to_expand));
	expand_var(token_list, var_idxs_to_expand, list_get_size(var_idxs_to_expand));
	merge_quotes(token_list);
	return (token_list);
}
