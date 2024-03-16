/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:27:56 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/15 15:31:49 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*check_for_cmd(char **path, char *cmd, t_fd_argvs *fd, t_flags flags)
{
	char	*path_2_cmd;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (!access(tmp, X_OK))
			path_2_cmd = tmp;
		if (!access(tmp, X_OK))
			break ;
		ft_free_n_null((void **)&tmp);
		i++;
	}
	if (!tmp)
		errors(-1, "Error command not found", fd, flags);
	return (path_2_cmd);
}