/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 18:25:46 by JFikents         ###   ########.fr       */
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

static char	*format_hostname(char *hostname, t_alloc_list *to_free)
{
	char	*temp;
	char	*point_position;

	if (!hostname)
		return (NULL);
	point_position = ft_strchr(hostname, '.');
	temp = ft_substr(hostname, 0, point_position - hostname + 1);
	hostname = temp;
	point_position = ft_strchr(hostname, '.');
	if (point_position)
		*point_position = ':';
	free_from_list(to_free, HOSTNAME);
	add_to_list(hostname, HOSTNAME, to_free);
	return (hostname);
}

static char	*get_hostname(t_alloc_list *to_free)
{
	extern char	**environ;
	char		hostname[100];
	pid_t		pid;
	int			pipe_fd[2];
	int			status;

	if (pipe(pipe_fd) == -1)
		clean_exit(to_free);
	pid = fork();
	if (pid == -1)
		clean_exit(to_free);
	if (!pid)
	{
		if (setup_out_pipe(pipe_fd))
			clean_exit(to_free);
		execve(check_for_cmd("hostname"), (char *[]){"hostname", NULL},
			environ);
	}
	waitpid(pid, NULL, 0);
	read(pipe_fd[PIPE_FD_READ], &hostname, 100);
	ft_close(&pipe_fd[PIPE_FD_READ]);
	ft_close(&pipe_fd[PIPE_FD_WRITE]);
	return (format_hostname(hostname, to_free));
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

char	*prompt(t_alloc_list *to_free)
{
	char	*temp;
	char	*prompt;
	char	*directory;
	char	*input;
	char	*host;

	directory = get_directory();
	// char *actual_hostname = get_hostname();
	host = ft_strjoin(CYAN"", get_hostname(to_free)); // TODO: do freeing in this scope
	// free(actual_hostname);
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
		clean_exit(to_free);
	return (input);
}
