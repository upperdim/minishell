/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/19 20:11:08 by JFikents         ###   ########.fr       */
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
	return (hostname);
}

static char	*get_hostname(void)
{
	extern char	**environ;
	pid_t		pid;
	int			pipe_fd[2];
	int			status;
	char		*hostname;

	if (pipe(pipe_fd) == -1)
		exit_perror(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit_perror(EXIT_FAILURE);
	if (!pid)
	{
		setup_out_pipe(pipe_fd);
		execve(find_path_to("hostname"), (char *[]){"hostname", NULL}, environ);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (NULL);
	hostname = get_next_line(pipe_fd[PIPE_FD_READ]);
	ft_close(&pipe_fd[PIPE_FD_READ]);
	ft_close(&pipe_fd[PIPE_FD_WRITE]);
	if (hostname == NULL)
		return (NULL);
	return (format_hostname(hostname));
}

static char	*get_directory(void)
{
	char	*cwd;
	char	*directory;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (NULL);
	directory = ft_strrchr(cwd, '/');
	directory = ft_strdup(directory + 1);
	return (ft_free_n_null((void **)&cwd), directory);
}

// consts below are only for norminette
char	*get_prompt(void)
{
	const char	*temp = get_hostname();
	const char	*directory = get_directory();
	const char	*host = ft_strjoin(CYAN"", temp);
	char		*prompt;

	if (!temp || !directory || !host)
		return (ft_free_n_null((void **)&temp),
			ft_free_n_null((void **)&directory),
			ft_free_n_null((void **)&host), NULL);
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(host, directory);
	ft_free_n_null((void **)&host);
	ft_free_n_null((void **)&directory);
	if (!temp)
		return (NULL);
	directory = ft_strjoin(temp, BLUE" ");
	ft_free_n_null((void **)&temp);
	if (!directory)
		return (NULL);
	temp = ft_strjoin(directory, get_user());
	ft_free_n_null((void **)&directory);
	if (!temp)
		return (NULL);
	prompt = ft_strjoin(temp, "$ "WHITE);
	return (ft_free_n_null((void **)&temp), prompt);
}
