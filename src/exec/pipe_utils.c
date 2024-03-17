/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:59:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 18:31:09 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_out_pipe(int p_fd[2], t_mallocated *to_free)
{
	errors((int [3]){ft_close(p_fd[P_READ]), 0, 0}, NULL, to_free);
	errors((int [3]){dup2(p_fd[P_WRITE], STDOUT_FILENO), 0, 0}, NULL, to_free);
	errors((int [3]){ft_close(p_fd[P_WRITE]), 0, 0}, NULL, to_free);
}

void	setup_in_pipe(int p_fd[2], t_mallocated *to_free)
{
	errors((int [3]){ft_close(p_fd[P_WRITE]), 0, 0}, NULL, to_free);
	errors((int [3]){dup2(p_fd[P_READ], STDIN_FILENO), 0, 0}, NULL, to_free);
	errors((int [3]){ft_close(p_fd[P_READ]), 0, 0}, NULL, to_free);
}

char	**format_path(char *env_path)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_substr(env_path, 5, ft_strlen(env_path) - 5);
	path = ft_split(tmp, ':');
	ft_free_n_null((void **)&tmp);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		ft_free_n_null((void **)&path[i]);
		path[i] = tmp;
		i++;
	}
	return (path);
}

char	*check_for_cmd(char *cmd, t_mallocated *to_free)
{
	char	*path_2_cmd;
	char	*tmp;
	int		i;
	char	**path;

	i = 0;
	path = format_path(getenv("PATH"));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!access(tmp, X_OK))
		{
			path_2_cmd = tmp;
			break ;
		}
		ft_free_n_null((void **)&tmp);
		i++;
	}
	if (!tmp)
		errors((int [3]){-1, UNKNOWN_COMMAND, 0}, NULL, to_free);
	return (path_2_cmd);
}
//! Original function from pipex needs to be modified
// char	**create_argv(char *argv[], char *input, t_mallocated *to_free)
// {
// 	char	**cmd_n_args;
// 	int		argvs_i;
// 	int		argv_i;
// 	int		cmd_i;

// 	argvs_i = 0;
// 	argv_i = 2 + flags.here_doc;
// 	fd->argvs = (char ***)ft_calloc((flags.cmd_count + 1), sizeof(char **));
// 	if (fd->argvs == NULL)
// 		errors(-1, "Error creating fd->argvs", fd, flags);
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
