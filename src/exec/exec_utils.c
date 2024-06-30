/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:15:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/30 10:48:17 by JFikents         ###   ########.fr       */
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

int	set_redir(t_token *redir)
{
	char	*file;
	int		original_fd;
	int		fd;

	while (redir != NULL)
	{
		original_fd = get_fd(redir);
		file = redir->next->value;
		if (redir->type == REDIR_TO)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND_TO)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_FROM)
			fd = open(file, O_RDONLY, 0644);
		else if (redir->type == HERE_DOC)
			fd = open(HEREDOC_FILE, O_RDONLY, 0644);
		if (fd == -1)
			return (ft_putstr_fd("minishell: Error opening file\n", 2), 1);
		if (dup2(fd, original_fd) == -1)
			return (ft_printf_fd(2, "minishell: %d: Bad file descriptor\n",
					original_fd), ft_close(&fd), 1);
		ft_close(&fd);
		redir = redir->next->next;
	}
	return (0);
}

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
		ft_close(&tmp->pipe[PIPE_FD_READ]);
		ft_close(&tmp->pipe[PIPE_FD_WRITE]);
		ft_free_n_null((void **)&tmp);
	}
}

static int	child_process_main(t_cmd *cmd)
{
	int	ret;

	if (check_if_heredoc(cmd->redirects))
		return (1);
	if (cmd->pipe[PIPE_FD_READ] != 0)
	{
		ret = setup_in_pipe(cmd->pipe);
		if (cmd->prev != NULL)
			ft_close(&cmd->prev->pipe[PIPE_FD_WRITE]);
		if (ret == -1)
			return (1);
	}
	if (cmd->pipe[PIPE_FD_WRITE] != 0)
	{
		ret = setup_out_pipe(cmd->pipe);
		if (cmd->next != NULL)
			ft_close(&cmd->next->pipe[PIPE_FD_READ]);
		if (ret == -1)
			return (1);
	}
	if (set_redir(cmd->redirects))
		return (1);
	ft_execve(cmd->argv);
	return (1);
}

pid_t	create_fork(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putendl_fd("minishell: Error creating fork", 2), 0);
	if (pid == 0)
		if (child_process_main(cmd))
			return (0);
	return (pid);
}
