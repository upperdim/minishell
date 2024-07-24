/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_tilda.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:05:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 03:06:34 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_eligible_for_exp(char *line, int i, char quote_type)
{
	if (line[i] != '~')
		return (FALSE);
	if (quote_type != NOT_QUOTE)
		return (FALSE);
	if (i > 0 && line[i - 1] != ' ')
		return (FALSE);
	if (line[i + 1] != '\0' && (line[i + 1] != ' ' && line[i + 1] != '/'))
		return (FALSE);
	return (TRUE);
}

int	detect_tld_exp(char *line, int len, t_list_int **p_tld_idxs_to_exp)
{
	char	quote_type;
	int		tilda_idx;
	int		i;

	quote_type = NOT_QUOTE;
	tilda_idx = 0;
	i = 0;
	while (i < len)
	{
		if (quote_type == NOT_QUOTE && (line[i] == '\"' || line[i] == '\''))
			quote_type = line[i];
		else if (line[i] == quote_type)
			quote_type = NOT_QUOTE;
		else if (line[i] == '~')
		{
			if (is_eligible_for_exp(line, i, quote_type))
				if (list_add(p_tld_idxs_to_exp, tilda_idx) == FAILURE)
					return (FAILURE);
			++tilda_idx;
		}
		++i;
	}
	return (SUCCESS);
}
