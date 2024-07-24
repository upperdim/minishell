/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:11:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/24 19:14:10 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_innecessary_pipes(t_cmd *cmd)
{
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	while (cmd)
	{
		ft_close(&cmd->pipe[PIPE_FD_READ]);
		ft_close(&cmd->pipe[PIPE_FD_WRITE]);
		cmd = cmd->next;
	}
}
