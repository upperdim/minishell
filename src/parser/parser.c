/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:29 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/07 17:20:22 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_instruction	*parse_line(char *input)
{
	t_instruction	*instruction;

	input = ft_strtrim(input, " ");
	if (!input || !*input)
	{
		if (input)
			free(input);
		return (NULL);
	}
	instruction = ft_calloc(1, sizeof(t_instruction));
	if (!instruction)
		return (free(input), NULL);
	if (ft_strchr(input, ' '))
		instruction->cmd = ft_substr(input, 0, ft_strchr(input, ' ') - input);
	else
		instruction->cmd = ft_strdup(input);
	return (free(input), instruction);
}
