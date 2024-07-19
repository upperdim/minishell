/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:34:15 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/19 18:14:54 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	This fierce quote exorcist will liberate the string with unwavering 
	determination by putting despicable and ignominious quote pairs through an
	unrelenting elimination process, mercilessly eradicating both of them with
	surgical precision, obliterating them from the face of the earth. This
	unyielding crusader against the oppression of textual boundaries declares a
	ceaseless battle of expunging the vestiges against the tyranny of quotation
	marks. No trace of these textual demarcations shall evade its vigilant
	gaze as it purges the string with an indomitable resolve. The ultimate
	unquotifier sends quotation marks from the string to a godforsaken realm of
	abyss never to be seen, heard or talked about again, eternally banished into
	the deepest and darkest of all voids. This is not just merely a utilitarian
	function. It is a profound manifestation of our collective hubris, a
	reflection of an endless quest for the existential resistance and rebellion
	against entropy that slowly consumes us all, a symbol of eternal struggle
	for liberation from our ultimate unavoidable destiny of a cold and slow 
	decay into homogenized singularity.
*/
static int	obliterate_quote_symbols(char **p_value, int *i)
{
	char	quote_type;
	int		next_quote_idx;

	if (*p_value == NULL)
		return (TRUE);
	quote_type = (*p_value)[*i];
	next_quote_idx = find_idx_of_nextc(*p_value, *i + 1, quote_type);
	if (next_quote_idx == -1)
		return (FALSE);
	str_replace_section(p_value, *i, *i, "");
	--next_quote_idx;
	str_replace_section(p_value, next_quote_idx, next_quote_idx, "");
	*i = next_quote_idx;
	return (TRUE);
}

/*
	Merge sections enclosed by quotes into respective tokens.
	Return TRUE upon success, FALSE upon encountering unclosed quotes.
*/
int	merge_quotes(t_token *token_list)
{
	t_token	*iter;
	size_t	i;
	int		last_quote_idx;

	iter = token_list;
	while (iter != NULL)
	{
		if (iter->type == STRING)
		{
			i = 0;
			while (i < ft_strlen(iter->value))
			{
				last_quote_idx = 1;
				if (iter->value[i] == '\'' || iter->value[i] == '\"')
					if (!obliterate_quote_symbols(&iter->value, &i))
						return (FALSE);
				++i;
			}
		}
		iter = iter->next;
	}
	return (TRUE);
}
