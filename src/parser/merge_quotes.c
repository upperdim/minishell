/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:34:15 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/24 17:23:34 by tunsal           ###   ########.fr       */
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
static int	obliterate_quote_symbols(t_merge_quotes_vars *v)
{
	char	quote_type;
	int		initial_next_q_idx;
	int		next_quote_idx;

	if (v->iter->value == NULL)
		return (TRUE);
	quote_type = v->iter->value[v->i];
	next_quote_idx = str_findc_idx(v->iter->value, v->i + 1, quote_type);
	initial_next_q_idx = next_quote_idx;
	if (next_quote_idx == -1)
		return (FALSE);
	if (str_replace_section(&v->iter->value, v->i, v->i, "") == FAILURE)
		exit_free_toklst_exp_idxs(v->token_list, v->exp_idxs, v->line);
	--next_quote_idx;
	if (str_replace_section(\
&v->iter->value, next_quote_idx, next_quote_idx, "") == FAILURE)
		exit_free_toklst_exp_idxs(v->token_list, v->exp_idxs, v->line);
	v->i = initial_next_q_idx - 2;
	return (TRUE);
}

void	init_merge_quote_vars(\
t_merge_quotes_vars *v, t_token *token_list, t_exp_idxs *exp_idxs, char *line)
{
	v->i = 0;
	v->token_list = token_list;
	v->iter = token_list;
	v->exp_idxs = exp_idxs;
	v->line = line;
}

/*
	Merge sections enclosed by quotes into respective tokens.
	Return TRUE upon success, FALSE upon encountering unclosed quotes.
*/
int	merge_quotes(t_token *token_list, t_exp_idxs *exp_idxs, char *line)
{
	t_merge_quotes_vars	v;

	init_merge_quote_vars(&v, token_list, exp_idxs, line);
	while (v.iter != NULL)
	{
		if (v.iter->type == STRING)
		{
			v.i = 0;
			while (v.i < strlen_null(v.iter->value))
			{
				if (v.iter->value[v.i] == '\'' || v.iter->value[v.i] == '\"')
					if (!obliterate_quote_symbols(&v))
						return (FALSE);
				++v.i;
			}
		}
		v.iter = v.iter->next;
	}
	return (TRUE);
}
