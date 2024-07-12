/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:56:57 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/12 19:24:44 by JFikents         ###   ########.fr       */
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
		return (ft_printf_fd(2, ERROR_MSG, "pipe", E_ALLOC), NULL);
	cmd->next->prev = cmd;
	cmd = cmd->next;
	cmd->pipe[PIPE_FD_READ] = pipe_fd[PIPE_FD_READ];
	return (cmd);
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
	return (ft_free_link_list((t_token **)&head_token), (t_cmd *)head_cmd);
}
