/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:00:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/23 17:03:21 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_limiter(char *line_stdin, char *limiter)
{
	int	new_line_index;

	new_line_index = ft_strlen(line_stdin) - 1;
	line_stdin[new_line_index] = '\0';
	if (ft_strncmp(line_stdin, limiter, ft_strlen(limiter) + 1) == 0)
		return (true);
	line_stdin[new_line_index] = '\n';
	return (false);
}

static char	*get_here_doc(char *limiter)
{
	char	*line;
	char	*tmp;
	char	*line_stdin;

	line = NULL;
	while (1)
	{
		ft_printf("> ");
		line_stdin = get_next_line(STDIN_FILENO);
		if ((line_stdin == NULL && ft_printf("\n")))
			break ;
		if (check_limiter(line_stdin, limiter) == true)
			break ;
		tmp = expand_heredoc(line_stdin);
		ft_free_n_null((void **)&line_stdin);
		if (tmp == NULL)
			return (ft_free_n_null((void **)&line), NULL);
		line_stdin = ft_strjoin(line, tmp);
		ft_free_n_null((void **)&tmp);
		ft_free_n_null((void **)&line);
		if (line_stdin == NULL)
			return (ft_printf_fd(2, ERROR_MSG, "heredoc", E_ALLOC), NULL);
		line = line_stdin;
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
