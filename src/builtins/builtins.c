/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/11 13:43:34 by JFikents         ###   ########.fr       */
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

int	exec_builtins(t_cmd	*cmd)
{
	const int	original_fd[3] = {dup(STDIN_FILENO), dup(STDOUT_FILENO),
		dup(STDERR_FILENO)};
	const char	*lowercase_cmd = dup_in_lowercase(cmd->argv[0]);
	const int	argc = count_strs_in_array(cmd->argv);
	int			exit_status;

	exit_status = do_all_redirections(cmd);
	if (lowercase_cmd == NULL || exit_status == EXIT_FAILURE)
		return (restore_fd(original_fd), free((void *)lowercase_cmd), 1);
	if (ft_strnstr(lowercase_cmd, "cd", 2))
		exit_status = cd(argc, cmd->argv);
	else if (ft_strnstr(lowercase_cmd, "echo", 4))
		exit_status = echo(cmd->argv);
	else if (ft_strnstr(lowercase_cmd, "env", 3))
		exit_status = env(argc);
	else if (ft_strnstr(lowercase_cmd, "export", 6))
		exit_status = export(argc, cmd->argv);
	else if (ft_strnstr(lowercase_cmd, "pwd", 3))
		exit_status = pwd();
	else if (ft_strnstr(lowercase_cmd, "exit", 4))
		exit_status = exit_bash(argc, cmd);
	else if (ft_strnstr(lowercase_cmd, "unset", 5))
		exit_status = unset_builtin(cmd->argv);
	restore_fd(original_fd);
	return (ft_free_n_null((void **)&lowercase_cmd), exit_status);
}
