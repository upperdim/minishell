/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/23 18:16:37 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_user(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
	{
		user = getenv("LOGNAME");
		if (!user)
			return (NULL);
	}
	return (user);
}

static char	*format_hostname(char *hostname)
{
	char	*temp;
	char	*point_position;

	point_position = ft_strchr(hostname, '.');
	temp = ft_substr(hostname, 0, point_position - hostname + 1);
	hostname = temp;
	point_position = ft_strchr(hostname, '.');
	if (point_position)
		*point_position = ':';
	return (hostname);
}

static char	*get_hostname(void)
{
	char		hostname[100];
	pid_t		pid;
	int			pipe_fd[2];

	ft_bzero(hostname, 100);
	if (pipe(pipe_fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		ft_execve((char *[]){check_for_cmd("hostname"), NULL}, NULL, pipe_fd);
	waitpid(pid, NULL, 0);
	read(pipe_fd[PIPE_FD_READ], &hostname, 100);
	ft_close(&pipe_fd[PIPE_FD_READ]);
	ft_close(&pipe_fd[PIPE_FD_WRITE]);
	if (!*hostname)
		return (NULL);
	return (format_hostname(hostname));
}

static char	*get_directory(void)
{
	char	*cwd;
	char	*directory;

	cwd = getcwd(NULL, 0);
	directory = ft_strrchr(cwd, '/');
	directory = ft_strdup(directory + 1);
	ft_free_n_null((void **)&cwd);
	return (directory);
}

char	*get_prompt()
{
	char	*temp;
	char	*prompt;
	char	*directory;
	char	*host;

	directory = get_directory();
	temp = get_hostname();
	host = ft_strjoin(CYAN"", temp);
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(host, directory);
	ft_free_n_null((void **)&host);
	ft_free_n_null((void **)&directory);
	directory = ft_strjoin(temp, BLUE" ");
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(directory, get_user());
	ft_free_n_null((void **)&directory);
	prompt = ft_strjoin(temp, "$ "WHITE);
	ft_free_n_null((void **)&temp);
	return (prompt);
}
