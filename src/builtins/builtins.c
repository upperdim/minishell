/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/08 20:46:16 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_strs_in_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		++i;
	return (i);
}

char	*dup_in_lowercase(const char *str)
{
	char	*lower;
	int		i;

	lower = ft_strdup(str);
	if (lower == NULL)
		return (NULL);
	i = -1;
	while (lower[++i])
		lower[i] = ft_tolower(lower[i]);
	return (lower);
}

int	set_last_process_exit_code(int exit_status)
{
	char	*exit_code;
	char	*var_exit_code;

	exit_code = ft_itoa(exit_status);
	if (exit_code == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), EXIT_FAILURE);
	var_exit_code = ft_strjoin("LAST_PROCESS_EXIT_CODE=", exit_code);
	ft_free_n_null((void **)&exit_code);
	if (var_exit_code == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), EXIT_FAILURE);
	if (add_env_var(var_exit_code) == NULL)
		return (ft_free_n_null((void **)&var_exit_code), EXIT_FAILURE);
	ft_free_n_null((void **)&var_exit_code);
	return (EXIT_SUCCESS);
}

void	restore_file_descriptors(const int original_fd[3])
{
	dup2(original_fd[ORIGINAL_STDIN], STDIN_FILENO);
	dup2(original_fd[ORIGINAL_STDOUT], STDOUT_FILENO);
	dup2(original_fd[ORIGINAL_STDERR], STDERR_FILENO);
}

// TODO implement unset
int	exec_builtins(t_cmd	*cmd)
{
	const int	original_fd[3] = {dup(STDIN_FILENO), dup(STDOUT_FILENO),
		dup(STDERR_FILENO)};
	const char	*lowercase_cmd = dup_in_lowercase(cmd->argv[0]);
	const int	argc = count_strs_in_array(cmd->argv);
	int			exit_status;

	if (lowercase_cmd == NULL)
		return (EXIT_FAILURE);
	do_all_redirections(cmd);
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
		exit_status = unset(argc, cmd->argv);
	restore_file_descriptors(original_fd);
	return (ft_free_n_null((void **)&lowercase_cmd), exit_status);
}
