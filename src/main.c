/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/06/01 17:13:52 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_environ(void)
{
	extern char	**environ;
	extern int	errno;
	int			env_c;
	char		**new_env;

	errno = 0;
	env_c = 0;
	while (environ[env_c])
		env_c++;
	new_env = ft_calloc(env_c + 1, sizeof(char *));
	if (!new_env)
		return (EXIT_FAILURE);
	env_c = 0;
	while (environ[env_c])
	{
		new_env[env_c] = ft_strdup(environ[env_c]);
		if (!new_env[env_c])
			return (ft_free_2d_array((void ***)&new_env, -1), EXIT_FAILURE);
		env_c++;
	}
	environ = new_env;
	return (0);
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
	char		*input;
	extern int	errno;

	if (init_environ())
		return (EXIT_FAILURE);
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
