/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/06/01 19:49:57 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_environ(void)
{
	extern char	**environ;
	extern int	errno;
	int			env_var_count;
	char		**new_env;

	errno = 0;
	env_var_count = 0;
	while (environ[env_var_count])
		env_var_count++;
	new_env = ft_calloc(env_var_count + 1, sizeof(char *));
	if (!new_env)
		return (EXIT_FAILURE);
	env_var_count = 0;
	while (environ[env_var_count])
	{
		new_env[env_var_count] = ft_strdup(environ[env_var_count]);
		if (!new_env[env_var_count])
			return (ft_free_2d_array((void ***)&new_env, -1), EXIT_FAILURE);
		env_var_count++;
	}
	environ = new_env;
	return (0);
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

	if (init_environ())
	{
		ft_printf_fd(2, E_GENERIC, "malloc", "Error initializing environment");
		return (EXIT_FAILURE);
	}
	input = NULL;
	set_signal_handlers();
	while (1)
	{
		input = get_input();
		if (input == NULL)
			return (clean_up(), 0);
		// parse_line(input);
		if (input == NULL)
			continue ;
		if (ft_strlen(input) > 0)
			add_history(input);
		ft_free_n_null((void **)&input);
	}
	return (clean_up(), errno);
}
