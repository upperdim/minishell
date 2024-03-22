/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/22 18:57:52 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initilizer(t_alloc_list *to_free, char **input)
{
	to_free->ptr = NULL;
	to_free->next = NULL;
	to_free->index = -1;
	*input = NULL;
}

int	main(void)
{
	t_alloc_list		to_free[1];
	char				*input;
	char				*prompt;

	initilizer(to_free, &input);
	set_signal_handlers();
	while (1)
	{
		free_from_list(to_free, INPUT);
		prompt = get_prompt(to_free);
		input = readline(prompt);
		ft_free_n_null((void **)&prompt);
		if (!input)
			clean_exit(to_free);
		input = parse_line(input, to_free);
		if (!input)
			continue ;
		builtins(input, to_free);
	}
	return (clean_exit(to_free), 0);
}
