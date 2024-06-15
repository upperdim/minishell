/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/15 19:56:21 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//! This function is from the original pipex project, needs to be modified.
// void	exec_cmd(char *cmd, char **argv)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == -1)
// 		errors(&pid, "Error forking", NULL);
// 	if (pid == 0)
// 	{
// 		execve(cmd, argv, NULL);
// 		errors(&pid, "Error execve", NULL);
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			status = WEXITSTATUS(status);
// 	}
// }

static t_cmd	*set_cmd_pipe(t_cmd *cmd)
{
	int			pipe_fd[2];
	extern int	errno;

	if (pipe(pipe_fd) == -1)
		exit_perror(errno);
	cmd->pipe[PIPE_FD_WRITE] = pipe_fd[PIPE_FD_WRITE];
	cmd->next = ft_calloc(1, sizeof(t_cmd));
	if (cmd->next == NULL)
		exit_error("Error allocating memory", 1);
	cmd = cmd->next;
	cmd->pipe[PIPE_FD_READ] = pipe_fd[PIPE_FD_READ];
	return (cmd);
}

t_cmd	*divide_tokens(t_token *token)
{
	const t_cmd	*head_cmd = ft_calloc(1, sizeof(t_cmd));
	t_cmd		*cmd;

	if (head_cmd == NULL)
		exit_error("Error allocating memory", 1);
	cmd = (t_cmd *)head_cmd;
	while (token != NULL)
	{
		if (token->type == STRING)
			add_token_last(&cmd->strs, &token);
		else if (token->type > STRING && token->type < PIPE)
			add_token_last(&cmd->redirects, &token);
		else if (token->type == PIPE)
		{
			cmd = set_cmd_pipe(cmd);
			token = token->next;
		}
	}
	return ((t_cmd *)head_cmd);
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
		argv[argc++] = token->value;
		token = token->next;
	}
	return (argv);
}

int	exec(t_token *token)
{
	t_cmd	*cmd;

	cmd = divide_tokens(token);
	cmd->argv = transform_to_array(token);
	if (cmd->argv == NULL)
		return (1);
	ft_free_link_list(token);
	return (0);
}
