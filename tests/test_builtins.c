/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:01 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/24 20:40:47 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static pid_t	start_minishell(int *pipe_write)
{
	pid_t	pid;
	int		pipe_in[2];
	int		fd_out;
	int		check_pipe;

	fd_out = open("tests/minishell.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	int		read_output_fd;
	pid_t	pid;
	int		status;
	char	*line;
	char	*prompt;
	char	*cwd;
	char	*echo_line;

	pid = start_minishell(&write_minishell);


//_ COMMANDS FOR MINISHELL _//
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("cd ..", write_minishell);
	ft_putendl_fd("pwd", write_minishell);
	ft_putendl_fd("echo Hello World", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnnm Hello World", write_minishell);
	ft_putendl_fd("echo -nnnnnnnnn Hello World", write_minishell);
	ft_putendl_fd("echo -n Hello World", write_minishell);
	ft_putendl_fd("echo Hello World-n", write_minishell);
	ft_putendl_fd("echo Hello World -n", write_minishell);
	ft_putendl_fd("exit 123", write_minishell);
	waitpid(pid, &status, WUNTRACED);


	read_output_fd = open("tests/minishell.out", O_RDONLY);

	//_ CHECKING EXIT STATUS TEST 1 _//
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 123)
			ft_putendl_fd("Test 1 exit status success", 1);
		else
			ft_putendl_fd("Test 1 exit status failed", 1);
	}
	else
		ft_putendl_fd("exit status is incorrect", 1);


	//_ CHECKING PROMPT TEST 1_//
	line = get_next_line(read_output_fd);
	prompt = get_prompt();

	if (ft_strncmp(line, prompt, ft_strlen(prompt)))
		ft_putendl_fd("Test 1 prompt failed", 1);
	else
		ft_putendl_fd("Test 1 prompt success", 1);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&prompt);


	//_ CHECKING PWD TEST 1 _//
	line = get_next_line(read_output_fd);
	cwd = getcwd(NULL, 0);

	if (ft_strncmp(line, cwd, ft_strlen(cwd)))
		ft_putendl_fd("Test 1 pwd failed", 1);
	else
		ft_putendl_fd("Test 1 pwd success", 1);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&cwd);


	//_ CHECKING PROMPT TEST 2 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);
	chdir("..");
	prompt = get_prompt();

	if (ft_strncmp(line, prompt, ft_strlen(prompt)))
		ft_putendl_fd("Test 2 prompt failed", 1);
	else
		ft_putendl_fd("Test 2 prompt success", 1);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&prompt);


	//_ CHECKING PWD TEST 2 _//
	line = get_next_line(read_output_fd);
	cwd = getcwd(NULL, 0);

	if (ft_strncmp(line, cwd, ft_strlen(cwd)))
		ft_putendl_fd("Test 2 pwd failed", 1);
	else
		ft_putendl_fd("Test 2 pwd success", 1);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&cwd);


	//_ CHECKING ECHO TEST 1 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);

	if (ft_strncmp(line, "Hello World", ft_strlen("Hello World")))
		ft_putendl_fd("Test 1 echo failed", 1);
	else
		ft_putendl_fd("Test 1 echo success", 1);
	ft_free_n_null((void **)&line);


	//_ CHECKING ECHO TEST 2 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);
	
	
	if (ft_strncmp(line, "-nnnnnnnnnm Hello World", ft_strlen("-nnnnnnnnnm Hello World")))
		ft_putendl_fd("Test 2 echo failed", 1);
	else
		ft_putendl_fd("Test 2 echo success", 1);


	//_ CHECKING ECHO TEST 3 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);
	prompt = get_prompt();
	echo_line = ft_strjoin("Hello World", prompt);
	ft_free_n_null((void **)&prompt);

	if (ft_strncmp(line, echo_line, ft_strlen(echo_line)))
		ft_putendl_fd("Test 3 echo failed", 1);
	else
		ft_putendl_fd("Test 3 echo success", 1);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&echo_line);


	//_ CHECKING ECHO TEST 4 _//
	line = get_next_line(read_output_fd);
	prompt = get_prompt();
	echo_line = ft_strjoin("Hello World", prompt);
	ft_free_n_null((void **)&prompt);

	if (ft_strncmp(line, echo_line, ft_strlen(echo_line)))
		ft_putendl_fd("Test 4 echo failed", 1);
	else
		ft_putendl_fd("Test 4 echo success", 1);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&echo_line);


	//_ CHECKING ECHO TEST 5 _//
	line = get_next_line(read_output_fd);

	if (ft_strncmp(line, "Hello World-n", ft_strlen("Hello World-n")))
		ft_putendl_fd("Test 5 echo failed", 1);
	else
		ft_putendl_fd("Test 5 echo success", 1);
	ft_free_n_null((void **)&line);


	//_ CHECKING ECHO TEST 6 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);

	if (ft_strncmp(line, "Hello World -n", ft_strlen("Hello World -n")))
		ft_putendl_fd("Test 6 echo failed", 1);
	else
		ft_putendl_fd("Test 6 echo success", 1);
	ft_free_n_null((void **)&line);


	//_ CHECKING EXIT TEST 1 _//
	line = get_next_line(read_output_fd);
	ft_free_n_null((void **)&line);
	line = get_next_line(read_output_fd);

	if (ft_strncmp(line, "exit", ft_strlen("exit")))
		ft_putendl_fd("Test 1 exit failed", 1);
	else
		ft_putendl_fd("Test 1 exit success", 1);
	ft_free_n_null((void **)&line);


	ft_close(&write_minishell);
}

	// unlink("tests/minishell.out");