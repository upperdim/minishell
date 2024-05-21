/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:28:50 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/21 13:14:26 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

pid_t	start_minishell_builtins(int *pipe_write)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("tests/logs/minishell_builtins.log", O_WRONLY | O_CREAT
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
		return ((void) ft_printf(GREEN"%s success\n"DEFAULT, test));
	ft_printf(RED"%s failed\n", test);
	ft_printf("Output:\t\t%s", output);
	if (!ft_strchr(output, '\n'))
		ft_putchar_fd('\n', 1);
	ft_printf("Expected:\t%s\n\n"DEFAULT, expected);
}

void	reset_tty(pid_t pid)
{
	chdir("minishell");
	if (pid)
		kill(pid, SIGKILL);
	ft_putstr_fd(DEFAULT, 1);
}

char	*get_test_input(int fd)
{
	char	*line;
	char	*test_input;
	char	*old_line;
	char	*dollar_sign_limiter;

	test_input = get_next_line(fd);
	line = NULL;
	dollar_sign_limiter = ft_strchr(test_input, '$');
	while (dollar_sign_limiter == NULL)
	{
		old_line = test_input;
		ft_free_n_null((void **)&line);
		test_input = ft_strjoin(old_line, line = get_next_line(fd));
		ft_free_n_null((void **)&old_line);
		dollar_sign_limiter = ft_strchr(line, '$');
	}
	return (ft_free_n_null((void **)&line), test_input);
}

void	compile_minishell(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		ft_execve((char *[]){check_for_cmd("make"), "-s", "re", "COLOR=0",
			NULL}, NULL, NULL);
	waitpid(pid, NULL, 0);
}
