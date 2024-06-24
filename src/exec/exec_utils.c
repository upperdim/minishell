/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:15:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/24 16:53:55 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(t_token *redir)
{
	int		fd;

	fd = -1;
	if (redir->type == REDIR_TO || redir->type == APPEND_TO)
		fd = 1;
	else if (redir->type == REDIR_FROM || redir->type == HERE_DOC)
		fd = 0;
	if (ft_isdigit(redir->value[0]))
		fd = ft_atoi(redir->value);
	return (fd);
}

// int	set_redir(t_cmd *cmd)
// {
// 	t_token	*redir;
// 	char	*file;
// 	int		fd;

// 	redir = cmd->redirects;
// 	while (redir != NULL)
// 	{
// 		fd = get_fd(cmd);
// 		redir = redir->next;
// 	}
// 	return (0);
// }

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while (*cmd != NULL)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		if (tmp->argv)
			ft_free_2d_array((void ***)&tmp->argv, FREE_ANY_SIZE);
		ft_free_link_list(tmp->strs);
		ft_free_link_list(tmp->redirects);
		ft_free_n_null((void **)&tmp);
	}
}
