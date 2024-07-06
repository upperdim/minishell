/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/30 11:09:07 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*set_cmd_pipe(t_cmd *cmd)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (NULL);
	cmd->pipe[PIPE_FD_WRITE] = pipe_fd[PIPE_FD_WRITE];
	cmd->next = ft_calloc(1, sizeof(t_cmd));
	if (cmd->next == NULL)
		return (ft_putstr_fd("Error allocating memory", 2), NULL);
	cmd->next->prev = cmd;
	cmd = cmd->next;
	cmd->pipe[PIPE_FD_READ] = pipe_fd[PIPE_FD_READ];
	return (cmd);
}

// ! USED FOR TESTING
static void	free_expected_tokens(t_token **token)
{
	if (*token == NULL)
		return ;
	while ((*token)->next != NULL)
	{
		ft_free_n_null((void **)&(*token)->prev);
		(*token) = (*token)->next;
	}
	ft_free_n_null((void **)&(*token)->prev);
	ft_free_n_null((void **)&(*token));
}

t_cmd	*divide_tokens(t_token *token)
{
	const t_cmd		*head_cmd = ft_calloc(1, sizeof(t_cmd));
	const t_token	*head_token = token;
	t_cmd			*cmd;

	if (head_cmd == NULL)
		return (ft_putstr_fd(E_ALLOC, 2), NULL);
	cmd = (t_cmd *)head_cmd;
	while (token != NULL)
	{
		if (token->type == STRING)
			add_token_last(&cmd->strs, &token);
		else if (token->type > STRING && token->type < PIPE)
		{
			add_token_last(&cmd->redirects, &token);
			token = token->next;
			add_token_last(&cmd->redirects, &token);
		}
		else if (token->type == PIPE)
			cmd = set_cmd_pipe(cmd);
		if (cmd == NULL)
			return (free_cmd((t_cmd **)&head_cmd),
				ft_free_link_list((t_token *)head_token), NULL);
		token = token->next;
	}
	//! return (ft_free_link_list((t_token **)&head_token), (t_cmd *)head_cmd); UNCOMMENT THIS LINE AFTER TESTING and remove the line below
	return (free_expected_tokens((t_token **)&head_token), (t_cmd *)head_cmd);
}

char	**transform_to_array(t_token *token)
{
	char	**argv;
	int		argc;

	argc = 1;
	while (token->next != NULL && ++argc)
		token = token->next;
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	while (token->prev != NULL)
		token = token->prev;
	argc = 0;
	while (token != NULL)
	{
		argv[argc++] = ft_strdup(token->value);
		token = token->next;
	}
	return (argv);
}

int	exec(t_token *token)
{
	const t_cmd	*head_cmd = divide_tokens(token);
	t_cmd		*cmd;
	pid_t		pid;
	int			status;

	if (head_cmd == NULL)
		return (exit_perror(errno), 1);
	cmd = (t_cmd *)head_cmd;
	while (cmd != NULL)
	{
		cmd->argv = transform_to_array(cmd->strs);
		if (cmd->argv == NULL)
			return (free_cmd((t_cmd **)&head_cmd), 1);
		builtins(cmd);
		pid = create_fork(cmd);
		if (pid == 0)
			return (free_cmd((t_cmd **)&head_cmd), 1);
		if (waitpid(pid, &status, WUNTRACED) == -1)
			return (free_cmd((t_cmd **)&head_cmd),
				exit_perror(WEXITSTATUS(status)), 1);
		cmd = cmd->next;
	}
	free_cmd((t_cmd **)&head_cmd);
	unlink(HEREDOC_FILE);
	return (0);
}
