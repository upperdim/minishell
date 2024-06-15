/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:20:20 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/15 18:23:55 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "parser.h"

enum	e_pipes
{
	PIPE_FD_READ,
	PIPE_FD_WRITE
};

enum e_and_or
{
	NONE,
	AND,
	OR,
};

typedef struct s_cmd
{
	char			**argv;
	t_token			*strs;
	t_token			*redirects;
	enum e_and_or	and_or;
	int				pipe[2];
	struct s_cmd	*next;
}	t_cmd;

// Token utilities
t_token	*isolate_token(t_token **token);
void	add_token_last(t_token **head, t_token **new);

// Parsing utilities
void	ft_free_link_list(t_token *split);

// Execution utilities
void	free_cmd(t_cmd **cmd);

#endif