/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_no_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/24 16:48:42 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#ifdef NO_COLOR

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


char	*get_prompt(void)
{
	char	*tmp_prompt;
	char	*prompt;
	char	*directory;
	char	*host;
	char	*user;

	directory = get_directory();
	host = get_hostname();
	user = get_user();
	tmp_prompt = ft_strjoin(host, directory);
	ft_free_n_null((void **)&host);
	ft_free_n_null((void **)&directory);
	prompt = ft_strjoin(tmp_prompt, " ");
	ft_free_n_null((void **)&tmp_prompt);
	tmp_prompt = ft_strjoin(prompt, user);
	ft_free_n_null((void **)&prompt);
	prompt = ft_strjoin(tmp_prompt, "$ ");
	ft_free_n_null((void **)&tmp_prompt);
	return (prompt);
}
#endif
