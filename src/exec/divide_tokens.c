/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:56:57 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/20 14:22:57 by JFikents         ###   ########.fr       */
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

static int	add_redirects_tokens(t_token **cmd_redirects, t_token **token)
{
	int	status;

	status = add_token_last(cmd_redirects, token);
	*token = (*token)->next;
	if (status != EXIT_FAILURE)
		status = add_token_last(cmd_redirects, token);
	return (status);
}

t_cmd	*divide_tokens(t_token *token)
{
	const t_cmd		*head_cmd = ft_calloc(1, sizeof(t_cmd));
	const t_cmd		*cmd = head_cmd;
	const t_token	*head_token = token;
	static int		status = EXIT_SUCCESS;

	if (head_cmd == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "Divide Tokens", E_ALLOC, 2),
			free_tokens((t_token *)head_token), NULL);
	while (token != NULL)
	{
		if (token->type == STRING)
			status = add_token_last((t_token **)&cmd->strs, &token);
		else if (token->type > STRING && token->type < PIPE)
			status = add_redirects_tokens((t_token **)&cmd->redirects, &token);
		else if (token->type == PIPE)
			cmd = set_cmd_pipe((t_cmd *)cmd);
		if (cmd == NULL || status == EXIT_FAILURE)
			return (free_cmd((t_cmd **)&head_cmd),
				free_tokens((t_token *)head_token), NULL);
		token = token->next;
	}
	return (free_tokens((t_token *)head_token), (t_cmd *)head_cmd);
}
