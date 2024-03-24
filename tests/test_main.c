/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:26:18 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/24 15:53:29 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	compile_minishell(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		ft_execve((char *[]){check_for_cmd("make"), NULL}, NULL, NULL);
	waitpid(pid, NULL, 0);
}

static void	test_builtins(void)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("tests/input.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	check_pipe = pipe(pipe_in);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
	{
		dup2(fd_out, STDOUT_FILENO);
		ft_close(&fd_out);
		setup_in_pipe(pipe_in);
		ft_execve((char *[]){"./minishell_builtins", NULL}, NULL, NULL);
	}
	waitpid(pid, NULL, WUNTRACED);
	ft_close(&pipe_in[PIPE_FD_READ]);
	ft_close(&pipe_in[PIPE_FD_WRITE]);
	ft_close(&fd_out);
}

int	main(void)
{
	compile_minishell();
	test_builtins();
	unlink("tests/input.txt");
	return (0);
}
