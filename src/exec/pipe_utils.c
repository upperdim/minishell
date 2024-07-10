/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:59:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/10 15:05:39 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_out_pipe(int p_fd[2])
{
	int	status;

	status = dup2(p_fd[PIPE_FD_WRITE], STDOUT_FILENO);
	if (status == -1)
	{
		ft_printf_fd(2, ERROR_MSG, "pipe", "Error duplicating file descriptor");
		return (-1);
	}
	status = ft_close(&p_fd[PIPE_FD_WRITE]);
	if (status == -1)
	{
		ft_printf_fd(2, ERROR_MSG, "pipe", "Error closing pipe");
		return (-1);
	}
	return (0);
}

int	setup_in_pipe(int p_fd[2])
{
	int	status;

	status = dup2(p_fd[PIPE_FD_READ], STDIN_FILENO);
	if (status == -1)
	{
		ft_printf_fd(2, ERROR_MSG, "pipe", "Error duplicating file descriptor");
		return (-1);
	}
	status = ft_close(&p_fd[PIPE_FD_READ]);
	if (status == -1)
	{
		ft_printf_fd(2, ERROR_MSG, "pipe", "Error closing pipe");
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
	if (!tmp)
		return (ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC), NULL);
	env_path = ft_split(tmp, ':');
	ft_free_n_null((void **)&tmp);
	if (!env_path)
		return (ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC), NULL);
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
		{
			ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC);
			return (ft_free_2d_array((void ***)&env_path, FREE_ANY_SIZE), NULL);
		}
		ft_free_n_null((void **)&env_path[i]);
		env_path[i] = tmp;
		i++;
	}
	return (env_path);
}

char	*find_path_to(char *cmd)
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
		if (!test_path)
			return (ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC), NULL);
		if (!access(test_path, X_OK))
			abs_path_cmd = test_path;
		else
			ft_free_n_null((void **)&test_path);
		i++;
	}
	if (!abs_path_cmd)
		ft_printf_fd(2, ERROR_MSG, cmd, "command not found");
	return (abs_path_cmd);
}

// It handles the execution of the command but it still needs the fork before.
void	ft_execve(t_cmd *cmd)
{
	extern char	**environ;
	char		*cmd_path;

	if (!cmd->argv || !cmd->argv[0])
		exit_error(NULL, 0);
	cmd_path = cmd->argv[0];
	if (access (cmd->argv[0], X_OK))
		cmd_path = find_path_to(cmd->argv[0]);
	if (!cmd_path)
	{
		free_cmd(&cmd);
		exit_error(NULL, EXIT_FAILURE);
	}
	execve(cmd_path, cmd->argv, environ);
	if (cmd_path != cmd->argv[0])
		ft_free_n_null((void **)&cmd_path);
	ft_printf_fd(2, ERROR_MSG_PERROR, cmd->argv[0]);
	if (cmd->argv[1])
		ft_printf_fd(2, "%s: ", cmd->argv[1]);
	perror(NULL);
	free_cmd(&cmd);
	exit_error(NULL, EXIT_FAILURE);
}
