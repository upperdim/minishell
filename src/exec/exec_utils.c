/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:15:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/24 19:19:15 by JFikents         ###   ########.fr       */
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

char	*get_here_doc(char *limiter)
{
	char	*line;
	char	*tmp;
	char	*line_stdin;

	line = NULL;
	tmp = NULL;
	line_stdin = NULL;
	while (1)
	{
		ft_free_n_null((void **)&line_stdin);
		ft_printf("> ");
		line_stdin = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line_stdin, limiter, ft_strlen(line_stdin) + 1))
			break ;
		tmp = ft_strjoin(line, line_stdin);
		ft_free_n_null((void **)&line);
		line = tmp;
	}
	ft_free_n_null((void **)&line_stdin);
	return (line);
}

int	trigger_here_doc(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	line = get_here_doc(limiter);
	ft_putstr_fd(line, fd);
	ft_close(&fd);
	ft_free_n_null((void **)&line);
	fd = open(TMP_FILE, O_RDONLY);
	return (fd);
}

int	set_redir(t_token *redir)
{
	char	*file;
	int		original_fd;
	int		new_fd;

	while (redir != NULL)
	{
		original_fd = get_fd(redir);
		file = redir->next->value;
		if (redir->type == REDIR_TO)
			new_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND_TO)
			new_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_FROM)
			new_fd = open(file, O_RDONLY, 0644);
		else if (redir->type == HERE_DOC)
			new_fd = trigger_here_doc(file);
		if (new_fd == -1)
			return (ft_putstr_fd("Error opening file", 2), 1);
		if (dup2(new_fd, original_fd) == -1)
			return (ft_close(&new_fd),
				ft_putstr_fd("Error duplicating file descriptor", 2), 1);
		ft_close(&new_fd);
		redir = redir->next;
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
