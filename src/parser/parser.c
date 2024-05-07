/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/07 21:08:00 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_instruction	*parse_line(char *input)
{
	t_instruction	*instruction;
	char			**split_input;

	if (!input || !*input)
		return (NULL);
	instruction = ft_calloc(1, sizeof(t_instruction));
	if (!instruction)
		return (NULL);
	split_input = ft_split(input, ' ');
	if (!split_input || !*split_input)
		return (free(instruction), NULL);
	instruction->cmd = *split_input;
	instruction->args = &split_input[1];
	instruction->flags.pipe_in = -1;
	instruction->flags.pipe_out = -1;
	instruction->next = NULL;
	return (instruction);
}
