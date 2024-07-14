/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/15 00:16:21 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_minishell(void)
{
	extern char	**environ;
	extern int	errno;

	errno = 0;
	environ = dup_environ();
	if (environ == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*get_input(void)
{
	char	*prompt;
	char	*input;

	prompt = get_prompt();
	if (prompt == NULL)
	{
		prompt = ft_strdup("minishell$ ");
		if (prompt == NULL)
			exit_error("minishell: Error allocating memory: malloc",
				EXIT_FAILURE);
	}
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	return (input);
}

int	main(void)
{
	char		*input;
	extern int	errno;

	if (init_minishell())
	{
		ft_printf_fd(2, ERROR_MSG, "malloc", "Error initializing environment");
		return (EXIT_FAILURE);
	}
	input = NULL;
	set_signal_handlers();
	while (1)
	{
		input = get_input();
		// TODO: this happens when it's EOF, in which case this can happen?
		if (input == NULL)
			return (clean_up(), 0);
		// parse_line(input);
		// TODO: why is this check here?
		if (input == NULL)
			continue ;
		if (ft_strlen(input) > 0)
			add_history(input);
		ft_free_n_null((void **)&input);
	}
	return (clean_up(), errno);
}
