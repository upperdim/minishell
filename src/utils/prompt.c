/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 19:58:16 by JFikents         ###   ########.fr       */
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

static char	*format_hostname(char *hostname, t_mallocated *to_free)
{
	char	*temp;
	char	*point_position;

	if (!hostname)
		return (NULL);
	point_position = ft_strchr(hostname, '.');
	temp = ft_substr(hostname, 0, point_position - hostname);
	hostname = temp;
	if (point_position)
		*point_position = ':';
	rm_from_free(to_free, HOSTNAME);
	needs_free(hostname, HOSTNAME, to_free);
	return (hostname);
}

static char	*hostname(t_mallocated *to_free)
{
	extern char	**environ;
	char		hostname[100];
	pid_t		pid;
	int			pipe_fd[2];
	int			status;

	status = pipe(pipe_fd);
	check((int [3]){status, 0, 0}, NULL, to_free);
	pid = fork();
	check((int [3]){pid, 0, 0}, NULL, to_free);
	if (!pid)
	{
		setup_out_pipe(pipe_fd, to_free);
		execve(check_for_cmd("hostname", to_free),
			(char *[]){"hostname", NULL}, environ);
		check((int [3]){-1, 0, 0}, NULL, to_free);
	}
	waitpid(pid, &status, 0);
	check((int [3]){status, 0, 0}, NULL, to_free);
	read(pipe_fd[OUT], &hostname, 100);
	return (format_hostname(hostname, to_free));
}

char	*prompt(t_mallocated *to_free)
{
	char	*temp;
	char	*prompt;
	char	*directory;
	char	*input;
	char	*host;

	temp = getcwd(NULL, 0);
	directory = ft_strrchr(temp, '/');
	ft_free_n_null((void **)&temp);
	directory = ft_strdup(directory + 1);
	host = ft_strjoin(CYAN"", hostname(to_free));
	temp = ft_strjoin(host, directory);
	ft_free_n_null((void **)&host);
	ft_free_n_null((void **)&directory);
	directory = ft_strjoin(temp, BLUE" ");
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(directory, get_user());
	ft_free_n_null((void **)&directory);
	prompt = ft_strjoin(temp, "$ "WHITE);
	ft_free_n_null((void **)&temp);
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	if (!input)
		check((int [3]){EXIT, 0, 0}, NULL, to_free);
	return (input);
}
