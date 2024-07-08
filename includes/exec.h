/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:20:20 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/04 17:57:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <sys/types.h>

# define HEREDOC_FILE ".here_doc.tmp"
# define E_ALLOC "Error allocating memory"
# define E_EXPORT "minishell: export: %s: not a valid identifier\n"

/*
ERROR_MSG_PERROR is meant to be used with ft_printf_fd and expects one string to
	be passed with it and perror() to be called after it
*/
# define ERROR_MSG_PERROR "minishell: %s: "

/*
ERROR_MSG is meant to be used with ft_printf_fd and expects two strings to be
	passed with it
*/
# define ERROR_MSG "minishell: %s: %s\n"

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
	struct s_cmd	*prev;
}	t_cmd;

// Token utilities
t_token	*dup_token(t_token *token);
t_token	*isolate_token(t_token **token);
void	add_token_last(t_token **head, t_token **new);

// Parsing utilities
void	ft_free_link_list(t_token *split);

// Execution utilities
int		count_strs_in_array(char **argv);
void	free_cmd(t_cmd **cmd);
int		set_redir(t_token *redirections);
int		check_if_heredoc(t_token *redirects);
pid_t	create_fork(t_cmd *cmd);
char	*dup_in_lowercase(const char *str);

#endif