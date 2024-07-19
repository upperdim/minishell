/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:34:15 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/19 06:07:06 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This fierce quote exorcist will put despicable and ignominious quote pairs
	through an unrelenting elimintion process, mercilessly eradicating both of
	them with surgical precision and obliterating them from the face of earth,
	liberating the string. This unyielding crusader against the oppression
	of textual boundaries declares a ceaseless battle against the tyranny
	of quotation marks. The ultimate unquotifier sends quote characters from
	the string to a godforsaken realm of abyss never to be seen, heard or talked
	about again, banished into the deepest and darkest void.
	This is not just a function. It is a mere manifestation of our collective
	hubris, a reflection of endless quest for the existential resistance and
	rebellion against entropy that slowly consumes us all, a symbol of eternal
	struggle for liberation from our inavoidable destiny.
*/
static void	obliterate_quote_symbols(char **p_value, int i)
{
	char	quote_type;
	int		next_quote_idx;
	
	if (*p_value == NULL)
		return ;
	quote_type = (*p_value)[i];
	next_quote_idx = find_idx_of_nextc(*p_value, i + 1, quote_type);
	if (next_quote_idx == -1)
		// TODO: Carry here and free every allocation
		exit_error("SyntaxError: unclosed quotes", EXIT_FAILURE);
	str_replace_section(p_value, i, i, "");
	str_replace_section(p_value, next_quote_idx - 1, next_quote_idx - 1, "");
}

void	merge_quotes(t_token *token_list)
{
	t_token 		*iter;
	int	i;
	
	iter = token_list;
	while (iter != NULL)
	{
		if (iter->type == STRING)
		{
			i = 0;
			while (i < strlen_null(iter->value))
			{
				if (iter->value[i] == '\'' || iter->value[i] == '\"')
					obliterate_quote_symbols(&iter->value, i);
				++i;
			}
		}
		iter = iter->next;
	}
}
