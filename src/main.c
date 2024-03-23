/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/23 18:15:57 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initilizer(char **input)
{
	*input = NULL;
}

int	main(void)
{

	char				*input;
	char				*prompt;

	initilizer(&input);
	set_signal_handlers();
	while (1)
	{	
		prompt = get_prompt();
		input = readline(prompt);
		ft_free_n_null((void **)&prompt);
		if (input == NULL)
			return (0);
		// parse_line(input);
		if (input == NULL)
			continue ;
		if (ft_strlen(input) > 0)
			add_history(*input);
		free(input);
		input = NULL;
	}
	return (0);
}
