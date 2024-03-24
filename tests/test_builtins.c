/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:01 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/24 20:02:32 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static pid_t	start_minishell(int *pipe_write)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("tests/minishell.out", O_RDWR | O_CREAT | O_TRUNC, 0644);
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

void	test_builtins(void)
{
	int		write_minishell;
	pid_t	pid;
	int		status;

	pid = start_minishell(&write_minishell);
	ft_putendl_fd("cd ..", write_minishell);
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("echo Hello Word", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnnm Hello Word", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnn Hello Word", write_minishell);
	ft_putendl_fd("echo -n Hello Word", write_minishell);
	ft_putendl_fd("echo Hello Word-n", write_minishell);
	ft_putendl_fd("echo Hello Word -n", write_minishell);
	ft_putendl_fd("exit 123", write_minishell);
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 123)
			ft_putendl_fd("exit status is correct", 1);
		else
			ft_putendl_fd("exit status is incorrect", 1);
	}
	else
		ft_putendl_fd("exit status is incorrect", 1);
	ft_close(&write_minishell);
}

	// unlink("tests/minishell.out");