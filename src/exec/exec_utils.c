/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:15:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/08 18:25:32 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(t_token *redir)
{
	int		fd;

	fd = -1;
	if (redir->type == REDIR_TO || redir->type == APPEND_TO)
		fd = 1;
	else if (redir->type == REDIR_FROM || redir->type == HERE_DOC)
		fd = 0;
	if (ft_isdigit(redir->value[0]))
		fd = ft_atoi(redir->value);
	return (fd);
}

static int	set_other_redirections(t_token *redir)
{
	char	*file;
	int		original_fd;
	int		fd;

	while (redir != NULL)
	{
		original_fd = get_fd(redir);
		file = redir->next->value;
		if (redir->type == REDIR_TO)
			fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND_TO)
			fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_FROM)
			fd = open(file, O_RDONLY, 0644);
		else if (redir->type == HERE_DOC)
			fd = open(HEREDOC_FILE, O_RDONLY, 0644);
		if (fd == -1)
			return (ft_putstr_fd("minishell: Error opening file\n", 2), 1);
		if (dup2(fd, original_fd) == -1)
			return (ft_printf_fd(2, "minishell: %d: Bad file descriptor\n",
					original_fd), ft_close(&fd), 1);
		ft_close(&fd);
		redir = redir->next->next;
	}
	return (0);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while ((*cmd)->prev != NULL)
		*cmd = (*cmd)->prev;
	while (*cmd != NULL)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		if (tmp->argv)
			ft_free_2d_array((void ***)&tmp->argv, FREE_ANY_SIZE);
		ft_free_link_list(tmp->strs);
		ft_free_link_list(tmp->redirects);
		ft_close(&tmp->pipe[PIPE_FD_READ]);
		ft_close(&tmp->pipe[PIPE_FD_WRITE]);
		ft_free_n_null((void **)&tmp);
	}
}

int	do_all_redirections(t_cmd *cmd)
{
	int	ret;

	if (check_if_heredoc(cmd->redirects))
		return (EXIT_FAILURE);
	if (cmd->pipe[PIPE_FD_READ] != 0)
	{
		ret = setup_in_pipe(cmd->pipe);
		if (ret == -1)
			return (EXIT_FAILURE);
	}
	if (cmd->pipe[PIPE_FD_WRITE] != 0)
	{
		ret = setup_out_pipe(cmd->pipe);
		if (ret == -1)
			return (EXIT_FAILURE);
	}
	if (set_other_redirections(cmd->redirects))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	is_builtin(const char *cmd)
{
	const char	*builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset", NULL};
	const char	*lowercase_cmd = dup_in_lowercase(cmd);
	int			i;

	if (lowercase_cmd == NULL)
		return (-1);
	i = -1;
	while (builtins[++i] != NULL)
	{
		if (ft_strnstr(lowercase_cmd, builtins[i], ft_strlen(builtins[i]) + 1))
		{
			ft_free_n_null((void **)&lowercase_cmd);
			return (true);
		}
	}
	ft_free_n_null((void **)&lowercase_cmd);
	return (false);
}

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
