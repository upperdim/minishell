/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:59:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 18:53:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_out_pipe(int p_fd[2])
{
	int	status;

	status = ft_close(&p_fd[PIPE_FD_READ]);
	if (status == -1)
	{
		ft_putstr_fd("Error closing pipe", 2);
		return (-1);
	}
	status = dup2(p_fd[PIPE_FD_WRITE], STDOUT_FILENO);
	if (status == -1)
	{
		ft_putstr_fd("Error duplicating file descriptor", 2);
		return (-1);
	}
	status = ft_close(&p_fd[PIPE_FD_WRITE]);
	if (status == -1)
	{
		ft_putstr_fd("Error closing pipe", 2);
		return (-1);
	}
	return (0);
}

int	setup_in_pipe(int p_fd[2])
{
	int	status;

	status = ft_close(&p_fd[PIPE_FD_WRITE]);
	if (status == -1)
	{
		ft_putstr_fd("Error closing pipe", 2);
		return (-1);
	}
	status = dup2(p_fd[PIPE_FD_READ], STDIN_FILENO);
	if (status == -1)
	{
		ft_putstr_fd("Error duplicating file descriptor", 2);
		return (-1);
	}
	status = ft_close(&p_fd[PIPE_FD_READ]);
	if (status == -1)
	{
		ft_putstr_fd("Error closing pipe", 2);
		return (-1);
	}
	return (0);
}

static char	**format_path(char *no_format_path)
{
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_substr(no_format_path, 5, ft_strlen(no_format_path) - 5);
	env_path = ft_split(tmp, ':');
	ft_free_n_null((void **)&tmp);
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		ft_free_n_null((void **)&env_path[i]);
		env_path[i] = tmp;
		i++;
	}
	return (env_path);
}

char	*check_for_cmd(char *cmd)
{
	char	*abs_path_cmd;
	char	*test_path;
	int		i;
	char	**env_path;

	i = 0;
	abs_path_cmd = NULL;
	env_path = format_path(getenv("PATH"));
	while (env_path[i] && !abs_path_cmd)
	{
		test_path = ft_strjoin(env_path[i], cmd);
		if (!access(test_path, X_OK))
			abs_path_cmd = test_path;
		else
			ft_free_n_null((void **)&test_path);
		i++;
	}
	if (!abs_path_cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
	}
	return (abs_path_cmd);
}

void	ft_execve(char **argv, char **envp, int pipe_fd[2])
{
	extern char	**environ;

	if (!argv || !argv[0])
		exit(0);
	if (pipe_fd)
	{
		if (setup_out_pipe(pipe_fd))
			exit(1);
	}
	if (envp)
		execve(argv[0], argv, envp);
	else
		execve(argv[0], argv, environ);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ft_strrchr(argv[0], '/') + 1, 2);
	ft_putstr_fd(": ", 2);
	if (argv[1])
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": ", 2);
	}
	perror(NULL);
	exit(1);
}
//! Original function from pipex needs to be modified
// char	**create_argv(char *argv[], char *input, t_alloc_list *to_free)
// {
// 	char	**cmd_n_args;
// 	int		argvs_i;
// 	int		argv_i;
// 	int		cmd_i;

// 	argvs_i = 0;
// 	argv_i = 2 + flags.here_doc;
// 	fd->argvs = (char ***)ft_calloc((flags.cmd_count + 1), sizeof(char **));
// 	if (fd->argvs == NULL)
// 		check(-1, "Error creating fd->argvs", fd, flags);
// 	while (argv_i <= flags.last_cmd)
// 	{
// 		cmd_n_args = ft_split(argv[argv_i], ' ');
// 		cmd_i = 0;
// 		while (cmd_n_args[cmd_i])
// 			cmd_i++;
// 		fd->argvs[argvs_i] = (char **)ft_calloc((cmd_i + 1), sizeof(char *));
// 		fd->argvs[argvs_i][0] = find_path(argv[argv_i++], fd, flags);
// 		cmd_i = 0;
// 		while (cmd_n_args[++cmd_i])
// 			fd->argvs[argvs_i][cmd_i] = cmd_n_args[cmd_i];
// 		argvs_i++;
// 		ft_free_n_null((void **)&cmd_n_args[0]);
// 		ft_free_n_null((void **)&cmd_n_args);
// 	}
// }
