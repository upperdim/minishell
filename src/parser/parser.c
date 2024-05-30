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

t_token	*parse_line(char *input)
{
	t_token	*head;

	if (!input || !*input)
		return (NULL);
	// head = ft_lexer(input);
	// ft_look_for_tokens_in_strs(head);
	// ft_expand_env_var(head);
	head = NULL;
	return (head);
}
