/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 18:22:45 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getuser(void)
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

static char	*hostname(t_mallocated *to_free)
{
	char	*hostname;
	char	*point_positon;
	pid_t	pid;
	int		pipe_fd[2];
	char	*argv;

	pipe(pipe_fd);
	pid = fork();
	errors((int [3]){pid, 0, 0}, NULL, to_free);
	if (pid != 0)
	{
		setup_out_pipe(pipe_fd, to_free);
		execve("/bin/hostname", (char *[]){"hostname", NULL}, NULL);
		exit(0);
	}
	point_positon = ft_strchr(hostname, '.');
	hostname = ft_substr(hostname, 0, point_positon - hostname);
	rm_from_free(to_free, HOSTNAME);
	needs_free(hostname, HOSTNAME, to_free);
	return (hostname);
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
	temp = ft_strjoin(directory, getuser());
	ft_free_n_null((void **)&directory);
	prompt = ft_strjoin(temp, "$ "WHITE);
	ft_free_n_null((void **)&temp);
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	if (!input)
		errors((int [3]){EXIT, 0, 0}, NULL, to_free);
	return (input);
}
