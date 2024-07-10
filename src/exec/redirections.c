/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:50:26 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/10 15:16:39 by JFikents         ###   ########.fr       */
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

static int	get_fd(t_token *redir)
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

static int	set_other_redirections(t_token *redir)
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

int	do_all_redirections(t_cmd *cmd)
{
	int	ret;

	if (check_if_heredoc(cmd->redirects))
		return (EXIT_FAILURE);
	if (cmd->pipe[PIPE_FD_READ] != 0)
	{
		ret = setup_in_pipe(cmd->pipe);
		if (ret == -1)
			return (EXIT_FAILURE);
	}
	if (cmd->pipe[PIPE_FD_WRITE] != 0)
	{
		ret = setup_out_pipe(cmd->pipe);
		if (ret == -1)
			return (EXIT_FAILURE);
	}
	if (set_other_redirections(cmd->redirects))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
