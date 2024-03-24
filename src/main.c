/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/24 13:09:00 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#ifndef BUILTINS

static void	initilizer(char **input)
{
	*input = NULL;
}

static char	*get_input(void)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt();
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	return (input);
}

int	main(void)
{
	char	*input;

	initilizer(&input);
	set_signal_handlers();
	while (1)
	{
		input = get_input();
		if (input == NULL)
			return (0);
		// parse_line(input);
		if (input == NULL)
			continue ;
		if (ft_strlen(input) > 0)
			add_history(input);
		free(input);
		input = NULL;
	}
	return (0);
}
#endif
