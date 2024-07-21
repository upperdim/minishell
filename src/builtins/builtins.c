/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/21 18:18:27 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	restore_fd(const int original_fd[3])
{
	dup2(original_fd[ORIGINAL_STDIN], STDIN_FILENO);
	ft_close((int *)&original_fd[ORIGINAL_STDIN]);
	dup2(original_fd[ORIGINAL_STDOUT], STDOUT_FILENO);
	ft_close((int *)&original_fd[ORIGINAL_STDOUT]);
	dup2(original_fd[ORIGINAL_STDERR], STDERR_FILENO);
	ft_close((int *)&original_fd[ORIGINAL_STDERR]);
}

static	enum e_builtin	select_builtin(const char *cmd)
{
	const char		*lowercase_cmd = dup_in_lowercase(cmd);
	enum e_builtin	builtin;

	if (lowercase_cmd == NULL)
		return (7);
	builtin = CD;
	if (ft_strncmp(lowercase_cmd, "cd", 3) == 0)
		builtin = CD;
	if (ft_strncmp(lowercase_cmd, "echo", 5) == 0)
		builtin = ECHO_BUILTIN;
	if (ft_strncmp(lowercase_cmd, "env", 4) == 0)
		builtin = ENV;
	if (ft_strncmp(lowercase_cmd, "export", 7) == 0)
		builtin = EXPORT;
	if (ft_strncmp(lowercase_cmd, "pwd", 4) == 0)
		builtin = PWD;
	if (ft_strncmp(lowercase_cmd, "exit", 5) == 0)
		builtin = EXIT;
	if (ft_strncmp(lowercase_cmd, "unset", 6) == 0)
		builtin = UNSET;
	ft_free_n_null((void **)&lowercase_cmd);
	return (builtin);
}

int	exec_builtins(t_cmd	*cmd)
{
	const int	original_fd[3] = {dup(STDIN_FILENO), dup(STDOUT_FILENO),
		dup(STDERR_FILENO)};
	const int	argc = count_strs_in_array(cmd->argv);
	const int	builtin = select_builtin(cmd->argv[0]);
	int			exit_status;

	exit_status = do_all_redirections(cmd);
	if (builtin == 7 || exit_status == EXIT_FAILURE)
		return (restore_fd(original_fd), 1);
	if (builtin == CD)
		exit_status = cd(argc, cmd->argv);
	else if (builtin == ECHO_BUILTIN)
		exit_status = echo(cmd->argv);
	else if (builtin == ENV)
		exit_status = env(argc);
	else if (builtin == EXPORT)
		exit_status = export(argc, cmd->argv);
	else if (builtin == PWD)
		exit_status = pwd();
	else if (builtin == EXIT)
		exit_status = exit_bash(argc, cmd);
	else if (builtin == UNSET)
		exit_status = unset_builtin(cmd->argv);
	restore_fd(original_fd);
	return (exit_status);
}
