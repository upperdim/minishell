/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:01 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 14:29:52 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static pid_t	start_minishell_builtins(int *pipe_write)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("tests/minishell_builtins_log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
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

static void send_commands_to_minishell(int write_minishell, pid_t pid,
	int *status)
{
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
}

void	test_builtins(void)
{
	extern char	**environ;
	pid_t		pid = 0;
	char		*cwd = NULL;
	char		*line = NULL;
	char		*prompt = NULL;
	char		*tmp_line = NULL;
	char		*str_exit_status = NULL;
	int			write_minishell = 0;
	int			read_output_fd = 0;
	int			fail_flag = 0;
	int			status = 0;
	int			i = 0;

	pid = start_minishell_builtins(&write_minishell);
	send_commands_to_minishell(write_minishell, pid, &status);
	

	read_output_fd = open("tests/minishell_builtins_log.txt", O_RDONLY);


	//_ CHECKING PROMPT TEST 1_//
	line = get_next_line(read_output_fd);
	prompt = get_prompt();

	print_feedback("Test 1 prompt", line, prompt);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&prompt);


	//_ CHECKING PWD TEST 1 _//
	line = get_next_line(read_output_fd);
	cwd = getcwd(NULL, 0);

	print_feedback("Test 1 pwd", line, cwd);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&cwd);


	//_ CHECKING PROMPT TEST 2 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);
	chdir("..");
	prompt = get_prompt();

	print_feedback("Test 2 prompt", line, prompt);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&prompt);


	//_ CHECKING PWD TEST 2 _//
	line = get_next_line(read_output_fd);
	cwd = getcwd(NULL, 0);

	print_feedback("Test 2 pwd", line, cwd);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&cwd);


	//_ CHECKING ECHO TESTS _//
	echo_test_1(read_output_fd);
	echo_test_2(read_output_fd);
	echo_test_3(read_output_fd);
	echo_test_4(read_output_fd);
	echo_test_5(read_output_fd);
	echo_test_6(read_output_fd);

	//_ CHECKING ENV TEST 1 _//
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


	//_ CHECKING EXIT TEST 1 _//
	line = get_next_line(read_output_fd);
	tmp_line = get_next_line(read_output_fd);
	while (line && tmp_line && *line && *tmp_line)
	{
		ft_free_n_null((void **)&line);
		line = get_next_line(read_output_fd);
		if (!line || !*line)
			break;
		ft_free_n_null((void **)&tmp_line);
		tmp_line = get_next_line(read_output_fd);
	}
	if (!line || !*line)
	{
		ft_free_n_null((void **)&line);
		line = tmp_line;
	}

	print_feedback("Test 1 exit", line, "exit");
	ft_free_n_null((void **)&line);


//_ CHECKING EXIT STATUS TEST 1 _//
	str_exit_status = ft_itoa(WEXITSTATUS(status));
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 255)
			ft_putendl_fd(GREEN"Test 1 exit status success", 1);
			print_feedback("Test 1 exit status", str_exit_status, "255");
}
	ft_free_n_null((void **)&str_exit_status);


	chdir("minishell");
	kill(pid, SIGKILL);


	ft_putstr_fd(DEFAULT, 1);
	ft_close(&write_minishell);
}

	// unlink("tests/minishell.out");