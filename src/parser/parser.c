/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/12 15:11:16 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_instruction	*parse_line(char *input)
{
	t_instruction	*instruction;
	t_split			*split_input;
	t_split			*pointer_to_free;
	int				i;

	if (!input || !*input)
		return (NULL);
	instruction = ft_calloc(1, sizeof(t_instruction));
	if (!instruction)
		return (NULL);
	split_input = ft_create_tokens(input);
	pointer_to_free = split_input;
	if (!split_input)
		return (free(instruction), NULL);
	instruction->cmd = split_input->result;
	split_input = split_input->next;
	i = 0;
	while (split_input)
	{
		instruction->args[i++] = split_input->result;
		split_input = split_input->next;
	}
	instruction->flags.pipe_in = -1;
	instruction->flags.pipe_out = -1;
	instruction->next = NULL;
	ft_free_n_null((void **)&pointer_to_free);
	return (instruction);
}
