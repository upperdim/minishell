/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append_tok.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:26:39 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 06:05:45 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   (Wrapper for Tokenizer)
   Append `to_append` to string pointed by `p_str`.
   Free everything until tokenizer upon error.
*/
void	str_append_tok(char **p_str, char *to_append, t_tokenizer_vars *v)
{
	if (str_append(p_str, to_append) == FAILURE)
		exit_free_tokenizer(ERR_MSG_MALLOC, v);
}

/*
   (Wrapper for Tokenizer)
   Append `char_to_append` to string pointed by `p_str`.
   Free everything until tokenizer upon error.
*/
void	str_appendc_tok(char **p_str, char char_to_append, t_tokenizer_vars *v)
{
	if (str_appendc(p_str, char_to_append) == FAILURE)
		exit_free_tokenizer(ERR_MSG_MALLOC, v);
}

/*
   (Wrapper for Tokenizer)
   Append `to_append_and_free` to string pointed by `p_str`.
   Free everything until tokenizer upon error.
*/
void	str_append_free_tok(\
char **p_str, char *to_append_and_free, t_tokenizer_vars *v)
{
	if (str_append_free(p_str, to_append_and_free) == FAILURE)
		exit_free_tokenizer(ERR_MSG_MALLOC, v);
}
