/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/21 17:32:19 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_pwd(void)
{
	extern char	**environ;
	const char	*cwd = getcwd(NULL, 0);
	char		*pwd_env_var;

	if (cwd == NULL)
		return (EXIT_FAILURE);
	pwd_env_var = ft_strjoin("PWD=", cwd);
	ft_free_n_null((void **)&cwd);
	if (pwd_env_var == NULL)
		return (ft_free_2d_array((void ***)&environ, -1), EXIT_FAILURE);
	add_env_var(pwd_env_var);
	ft_free_n_null((void **)&pwd_env_var);
	return (EXIT_SUCCESS);
}

static int	init_terminal_options(void)
{
	struct termios	terminal_config;

	tcgetattr(STDIN_FILENO, &terminal_config);
	terminal_config.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal_config);
	return (EXIT_SUCCESS);
}

static int	init_minishell(void)
{
	extern char		**environ;
	extern int		errno;

	errno = 0;
	environ = dup_environ();
	if (environ == NULL)
		return (EXIT_FAILURE);
	if (init_pwd())
		return (EXIT_FAILURE);
	if (init_terminal_options())
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
// !USE for testing
	// if (isatty(fileno(stdin)))
	// 	input = readline(prompt);
	// else
	// {
	// 	char	*line;
	// 	line = get_next_line(fileno(stdin));
	// 	input = ft_strtrim(line, "\n");
	// 	free(line);
	// }

int	main(void)
{
	char		*input;
	extern int	errno;
	t_token		*token_list;

	if (init_minishell())
	{
		ft_printf_fd(2, ERROR_MSG, "malloc", "Error initializing environment");
		return (EXIT_FAILURE);
	}
	input = NULL;
	while (errno == 0)
	{
		set_signal_handlers_mode(INTERACTIVE);
		input = get_input();
		if (input == NULL)
			return (exit_bash(1, NULL));
		token_list = parse(input);
		if (ft_strlen(input) > 0)
			add_history(input);
		set_signal_handlers_mode(EXECUTION);
		errno = exec(token_list);
		ft_free_n_null((void **)&input);
	}
	return (clean_up(), errno);
}
