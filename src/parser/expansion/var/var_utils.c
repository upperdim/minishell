/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:08:46 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 00:10:18 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_exp_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	replace_tok_val_section(\
t_token *tok, int s, int e, char *replace_with, int *p_value_len)
{
	str_replace_section(&tok->value, s, e, replace_with);
	free(replace_with);
	*p_value_len = ft_strlen(tok->value);
}

int	is_prev_here_doc(t_token *tok)
{
	if (tok->prev == NULL)
		return (FALSE);
	if (tok->prev->type == HERE_DOC)
		return (TRUE);
	return (FALSE);
}
