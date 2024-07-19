/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:00:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/27 16:54:29 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_here_doc(char *limiter)
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
		if (ft_strncmp(line_stdin, limiter, ft_strlen(line_stdin) - 1) == 0)
			break ;
		tmp = ft_strjoin(line, line_stdin);
		ft_free_n_null((void **)&line);
		line = tmp;
	}
	ft_free_n_null((void **)&line_stdin);
	return (line);
}

int	check_if_heredoc(t_token *redirects)
{
	char	*line;
	int		fd;

	line = NULL;
	while (redirects != NULL)
	{
		if (redirects->type == HERE_DOC)
		{
			fd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (1);
			set_signal_handlers_mode(HEREDOC);
			line = get_here_doc(redirects->next->value);
			set_signal_handlers_mode(EXECUTION);
			if (line)
				ft_putstr_fd(line, fd);
			ft_close(&fd);
		}
		ft_free_n_null((void **)&line);
		redirects = redirects->next->next;
	}
	return (0);
}
