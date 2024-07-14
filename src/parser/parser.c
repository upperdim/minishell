/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/15 01:36:28 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_quotes(char *line)
{
	char quote_type;
	int	len;
	int	i;

	quote_type = NULL;
	len = ft_strlen(line);
	i = 0;
	while (i < len)
	{
		if (quote_type == NULL && (line[i] == '\'' || line[i] == '\"'))
			quote_type = line[i];
		else if (quote_type == line[i])
			quote_type = NULL;
		++i;
	}
	return (quote_type == NULL);
}

// void	init_parser_vars(t_pvars *pvars, char *line)
// {
// 	pvars->line = line;
// 	pvars->len = ft_strlen(line);
// 	pvars->head = NULL;
// }

t_token	*parse_line(char *line)
{
	t_pvars		pvars;
	t_token 	*token_list;
	t_list_int	*tilda_idxs_to_expand;

	if (line == NULL || *line == NULL)
		return (NULL);
	// init_parser_vars(&pvars, line);
	token_list = NULL;
	if (validate_quotes == FALSE)
		exit_error("minishell: SyntaxError: unclosed quotes", EXIT_FAILURE);
	detect_tilda_expansions(line, tilda_idxs_to_expand);

	return (token_list);
}
