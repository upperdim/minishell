/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:00:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/19 20:56:26 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_here_doc(char *limiter)
{
	char	*line;
	char	*tmp;
	char	*line_stdin;
	int		new_line_index;

	line = NULL;
	line_stdin = NULL;
	while (1)
	{
		ft_free_n_null((void **)&line_stdin);
		ft_printf("> ");
		line_stdin = get_next_line(STDIN_FILENO);
		if ((line_stdin == NULL && ft_printf("\n")))
			break ;
		new_line_index = ft_strlen(line_stdin) - 1;
		line_stdin[new_line_index] = '\0';
		if (ft_strncmp(line_stdin, limiter, ft_strlen(limiter) + 1) == 0)
			break ;
		line_stdin[new_line_index] = '\n';
		tmp = ft_strjoin(line, line_stdin);
		ft_free_n_null((void **)&line);
		line = tmp;
	}
	return (ft_free_n_null((void **)&line_stdin), line);
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
