/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/17 17:48:21 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initilizer(t_mallocated *to_free, char **input)
{
	to_free->ptr = NULL;
	to_free->next = NULL;
	to_free->index = -1;
	*input = NULL;
}

int	main(void)
{
	t_mallocated		to_free[1];
	char				*input;

	initilizer(to_free, &input);
	set_signal_handlers();
	while (1)
	{
		rm_from_free(to_free, INPUT);
		input = prompt(to_free);
		input = parse_line(input, to_free);
		if (!input)
			continue ;
		builtins(input, to_free);
	}
	return (errors((int [3]){EXIT, 0, 0}, NULL, to_free), 0);
}
