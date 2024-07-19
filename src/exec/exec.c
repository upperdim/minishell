/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/19 21:25:02 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_msg_execve(t_cmd *cmd)
{
	struct stat	buf;

	buf.st_mode = 0;
	stat(cmd->argv[0], &buf);
	if (S_ISDIR(buf.st_mode))
		ft_printf_fd(2, ERROR_MSG, cmd->argv[0], "Is a directory");
	else if (cmd->argv[0][0] == '.' || cmd->argv[0][0] == '/')
	{
		ft_printf_fd(2, ERROR_MSG_PERROR, cmd->argv[0]);
		perror(NULL);
	}
	else
		ft_printf_fd(2, ERROR_MSG, cmd->argv[0], "command not found");
}

void	ft_execve(t_cmd *cmd)
{
	extern char	**environ;
	char		*cmd_path;

	if (!cmd->argv || !cmd->argv[0])
		exit_error(NULL, 0);
	cmd_path = cmd->argv[0];
	if (access (cmd->argv[0], X_OK))
		cmd_path = find_path_to(cmd->argv[0]);
	if (!cmd_path)
	{
		error_msg_execve(cmd);
		free_cmd(&cmd);
		exit_error(NULL, EXIT_FAILURE);
	}
	execve(cmd_path, cmd->argv, environ);
	if (cmd_path != cmd->argv[0])
		ft_free_n_null((void **)&cmd_path);
	error_msg_execve(cmd);
	free_cmd(&cmd);
	exit_error(NULL, EXIT_FAILURE);
}

static void	open_fd(t_token *redir)
{
	int	fd;

	while (redir != NULL)
	{
		fd = 0;
		if (redir->type == REDIR_TO)
			fd = open(redir->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND_TO)
			fd = open(redir->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_FROM)
			fd = open(redir->next->value, O_RDONLY);
		if (fd == -1)
			return (ft_printf_fd(2, ERROR_MSG_PERROR, redir->next->value),
				perror(NULL), (void)ft_close(&fd));
		if (fd)
			close(fd);
		redir = redir->next->next;
	}
}

pid_t	execute_cmd(t_cmd *cmd)
{
	pid_t		pid;
	int			builtin;

	if (check_if_heredoc(cmd->redirects))
		return (EXIT_FAILURE);
	if (cmd->argv == (void *)1)
		return (open_fd(cmd->redirects), BUILTIN_EXECUTED);
	builtin = is_builtin(cmd->argv[0]);
	if (builtin == true)
		return (set_last_process_exit_code(exec_builtins(cmd)),
			BUILTIN_EXECUTED);
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
