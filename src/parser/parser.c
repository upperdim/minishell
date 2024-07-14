/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/30 14:45:51 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	init_parser_vars(t_pvars *pvars, char *line)
// {
// 	pvars->line = line;
// 	pvars->len = ft_strlen(line);
// 	pvars->head = NULL;
// }

t_token	*parse_line(char *line)
{
	t_pvars pvars;
	t_token *head;

	if (line == NULL || *line == NULL)
		return (NULL);
	// init_parser_vars(&pvars, line);
	head = NULL;

	return (head);
}
