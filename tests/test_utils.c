/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:28:50 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/29 13:03:21 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

pid_t	start_minishell_builtins(int *pipe_write)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("logs/minishell_builtins.log", O_WRONLY | O_CREAT
			| O_APPEND, 0644);
	check_pipe = pipe(pipe_in);
	if (check_pipe == -1)
		exit(EXIT_FAILURE);
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
	ft_close(&fd_out);
	ft_close(&pipe_in[PIPE_FD_READ]);
	*pipe_write = pipe_in[PIPE_FD_WRITE];
	return (pid);
}

void	print_feedback(char *test, char *output, char *expected)
{
	if (!ft_strncmp(output, expected, ft_strlen(expected)))
		return ((void) ft_printf(GREEN"%s success\n", test));
	ft_printf(RED"%s failed\n", test);
	ft_printf("Output:\t\t%s", output);
	if (!ft_strchr(output, '\n'))
		ft_putchar_fd('\n', 1);
	ft_printf("Expected:\t%s\n\n", expected);
}

void	reset_tty(pid_t pid)
{
	chdir("minishell");
	if (pid)
		kill(pid, SIGKILL);
	ft_putstr_fd(DEFAULT, 1);
}
