/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/21 19:05:22 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*format_hostname(char *hostname)
{
	char	*temp;
	char	*point_position;
	char	*new_line;

	point_position = ft_strchr(hostname, '.');
	temp = ft_substr(hostname, 0, point_position - hostname + 1);
	ft_free_n_null((void **)&hostname);
	if (temp == NULL)
		return (NULL);
	hostname = temp;
	point_position = ft_strchr(hostname, '.');
	if (point_position)
		*point_position = ':';
	new_line = ft_strchr(hostname, '\n');
	if (new_line)
		*new_line = ' ';
	temp = ft_strjoin("HOSTNAME=", hostname);
	ft_free_n_null((void **)&hostname);
	add_env_var(temp);
	ft_free_n_null((void **)&temp);
	hostname = getenv("HOSTNAME");
	return (hostname);
}

static pid_t	execute_hostname(int pipe_fd[2])
{
	extern char	**environ;
	pid_t		pid;

	pid = fork();
	if (pid == -1)
		exit_perror(EXIT_FAILURE);
	if (pid == 0)
	{
		setup_out_pipe(pipe_fd);
		ft_close(&pipe_fd[PIPE_FD_READ]);
		execve(find_path_to("hostname"), (char *[]){"hostname", NULL}, environ);
		ft_free_2d_array((void ***)&environ, -1);
	}
	return (pid);
}

static char	*get_hostname(void)
{
	pid_t	pid;
	int		status;
	char	*hostname;
	int		pipe_fd[2];

	hostname = getenv("HOSTNAME");
	if (hostname)
		return (hostname);
	if (pipe(pipe_fd) == -1)
		exit_perror(EXIT_FAILURE);
	pid = execute_hostname(pipe_fd);
	ft_close(&pipe_fd[PIPE_FD_WRITE]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (NULL);
	hostname = get_next_line(pipe_fd[PIPE_FD_READ]);
	ft_close(&pipe_fd[PIPE_FD_READ]);
	if (hostname == NULL)
		return (NULL);
	return (format_hostname(hostname));
}

static char	*get_directory(void)
{
	char	*cwd;
	char	*directory;

	cwd = getenv("PWD");
	if (cwd == NULL)
		return (NULL);
	directory = ft_strrchr(cwd, '/');
	directory = ft_strdup(directory + 1);
	return (directory);
}

// consts below are only for norminette
char	*get_prompt(void)
{
	const char	*directory = get_directory();
	char		*temp;
	char		*prompt;

	if (directory == NULL)
		return (NULL);
	temp = ft_strjoin(get_hostname(), directory);
	ft_free_n_null((void **)&directory);
	if (temp == NULL)
		return (NULL);
	prompt = ft_strjoin(temp, " ");
	ft_free_n_null((void **)&temp);
	if (prompt == NULL)
		return (NULL);
	temp = ft_strjoin(prompt, getenv("USER"));
	ft_free_n_null((void **)&prompt);
	if (!temp)
		return (NULL);
	prompt = ft_strjoin(temp, "$ ");
	return (ft_free_n_null((void **)&temp), prompt);
}
