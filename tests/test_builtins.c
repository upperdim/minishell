/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:01 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 15:21:17 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static pid_t	start_minishell_builtins(int *pipe_write)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("tests/minishell_builtins_log.txt", O_WRONLY | O_CREAT
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

static pid_t send_commands_to_minishell(int *status)
{
	pid_t	pid;
	int		write_minishell;

	pid = start_minishell_builtins(&write_minishell);
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("cd ..", write_minishell);
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("echo Hello World", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnnm Hello World", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnn Hello World", write_minishell);
	ft_putendl_fd("echo -n Hello World", write_minishell);
	ft_putendl_fd("echo Hello World-n", write_minishell);
	ft_putendl_fd("echo Hello World -n", write_minishell);
	ft_putendl_fd("env", write_minishell);
	system("leaks minishell_builtins");
	ft_putendl_fd("exit -1", write_minishell);
	usleep(100000);
	kill(pid, SIGSTOP);
	waitpid(pid, status, WUNTRACED);
	ft_close(&write_minishell);
	return (pid);
}

static void	pwd_test(int read_output_fd)
{
	static int	i = 1;
	char		*output;
	char		*cwd;
	char		*test_str;
	char		*test_num_str;

	output = get_next_line(read_output_fd);
	test_str = ft_strjoin("Test ", test_num_str = ft_itoa(i++));
	ft_free_n_null((void **)&test_num_str);
	test_num_str = ft_strjoin(test_str, " pwd");
	ft_free_n_null((void **)&test_str);
	test_str = test_num_str;
	print_feedback(test_str, output, cwd = getcwd(NULL, 0));
	ft_free_n_null((void **)&test_str);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&cwd);
}

static void	prompt_test(int read_output_fd)
{
	static int	i = 1;
	char		*output;
	char		*prompt;
	char		*test_str;
	char		*test_num_str;

	output = get_next_line(read_output_fd);
	test_str = ft_strjoin("Test ", test_num_str = ft_itoa(i++));
	ft_free_n_null((void **)&test_num_str);
	test_num_str = ft_strjoin(test_str, " prompt");
	ft_free_n_null((void **)&test_str);
	test_str = test_num_str;
	print_feedback(test_str, output, prompt = get_prompt());
	ft_free_n_null((void **)&test_str);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&prompt);
}

static void	env_test(int read_output_fd)
{
	int			i;
	char		*line;
	extern char	**environ;
	int			fail_flag;

	fail_flag = 0;
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	i = -1;
	while (environ[++i])
	{
		line = get_next_line(read_output_fd);
		if (ft_strncmp(line, environ[i], ft_strchr(environ[i], '=') - environ[i]))
		{
			ft_printf(RED"Output:\t\t%sExpected:\t%s\n\n", line, environ[i]);
			fail_flag = 1;
		}
		ft_free_n_null((void **)&line);
	}
	if (!environ[i] && !fail_flag)
	ft_putendl_fd(GREEN"Test 1 env success", 1);
}

static void	reset_tty(pid_t pid)
{
	chdir("minishell");
	if (pid)
		kill(pid, SIGKILL);
	ft_putstr_fd(DEFAULT, 1);
}

void	test_builtins(void)
{
	extern char	**environ;
	pid_t		pid;
	char		*line;
	int			read_output_fd;
	int			status;

	read_output_fd = open("tests/minishell_builtins_log.txt", O_RDONLY);
	pid = send_commands_to_minishell(&status);
	prompt_test(read_output_fd);
	pwd_test(read_output_fd);
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	chdir("..");
	prompt_test(read_output_fd);
	pwd_test(read_output_fd);
	echo_test_1(read_output_fd);
	echo_test_2(read_output_fd);
	echo_test_3(read_output_fd);
	echo_test_4(read_output_fd);
	echo_test_5(read_output_fd);
	echo_test_6(read_output_fd);
	env_test(read_output_fd);
	exit_test_1(read_output_fd, status);
	reset_tty(pid);
}
