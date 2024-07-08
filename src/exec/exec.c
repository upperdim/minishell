/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/08 20:56:56 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	execute_cmd(t_cmd *cmd)
{
	pid_t		pid;
	int			exit_code;
	int			builtin;

	builtin = is_builtin(cmd->argv[0]);
	if (builtin == true)
	{
		exit_code = exec_builtins(cmd);
		set_last_process_exit_code(exit_code);
		return (BUILTIN_EXECUTED);
	}
	if (builtin == -1)
		return (ft_printf_fd(2, ERROR_MSG, cmd->argv[0], E_ALLOC),
			EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		return (ft_printf_fd(2, ERROR_MSG, cmd->argv[0], "Error creating fork"),
			EXIT_FAILURE);
	if (pid == 0)
	{
		if (do_all_redirections(cmd))
			return (EXIT_FAILURE);
		ft_execve(cmd);
	}
	return (pid);
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
			return (free_cmd(&cmd), EXIT_FAILURE);
		pid = execute_cmd(cmd);
		if (pid != BUILTIN_EXECUTED && pid == EXIT_FAILURE)
			return (free_cmd(&cmd), EXIT_FAILURE);
		if (pid != BUILTIN_EXECUTED && waitpid(pid, &status, WUNTRACED) == -1)
			return (free_cmd(&cmd), exit_perror(WEXITSTATUS(status)), 1);
		if (pid != BUILTIN_EXECUTED && WIFEXITED(status))
			set_last_process_exit_code(WEXITSTATUS(status));
		else if (pid != BUILTIN_EXECUTED && WIFSIGNALED(status))
			set_last_process_exit_code(WTERMSIG(status) + 128);
		cmd = cmd->next;
	}
	return (unlink(HEREDOC_FILE), free_cmd((t_cmd **)&head_cmd), EXIT_SUCCESS);
}
