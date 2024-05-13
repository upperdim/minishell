/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/13 19:03:07 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_args(t_split *split_input)
{
	int	i;

	i = 0;
	while (split_input)
	{
		i++;
		split_input = split_input->next;
	}
	return (i);
}

static int	ft_add_tokens_to_instructions(t_instruction *instruction,
	t_split *split_input)
{
	int	i;
	int	argc;

	instruction->cmd = split_input->result;
	split_input = split_input->next;
	i = 0;
	argc = ft_count_args(split_input);
	instruction->args = ft_calloc(argc + 1, sizeof(char *));
	if (!instruction->args)
		return (1);
	while (split_input)
	{
		instruction->args[i++] = split_input->result;
		split_input = split_input->next;
	}
	return (0);
}

t_instruction	*parse_line(char *input)
{
	t_instruction	*instruction;
	t_split			*split_input;
	t_split			*tmp;
	int				check;

	if (!input || !*input)
		return (NULL);
	instruction = ft_calloc(1, sizeof(t_instruction));
	if (!instruction)
		return (NULL);
	split_input = ft_create_tokens(input);
	if (!split_input)
		return (ft_free_n_null((void **)&instruction), NULL);
	check = ft_add_tokens_to_instructions(instruction, split_input);
	if (check)
		return (ft_free_n_null((void **)&instruction),
			ft_free_split(split_input), NULL);
	instruction->flags.pipe_in = -1;
	instruction->flags.pipe_out = -1;
	while (split_input)
	{
		tmp = split_input;
		split_input = split_input->next;
		ft_free_n_null((void **)&tmp);
	}
	return (instruction);
}
