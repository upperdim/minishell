/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/03 16:03:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		++i;
	return (i);
}

static char	*lowercase(const char *str)
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
		return (ft_putstr_fd(E_ALLOC, 2), 1);
	var_exit_code = ft_strjoin("LAST_PROCESS_EXIT_CODE=", exit_code);
	ft_free_n_null((void **)&exit_code);
	if (var_exit_code == NULL)
		return (ft_putstr_fd(E_ALLOC, 2), EXIT_FAILURE);
	if (add_env_var(var_exit_code) == NULL)
		return (ft_free_n_null((void **)&var_exit_code), EXIT_FAILURE);
	ft_free_n_null((void **)&var_exit_code);
	return (EXIT_SUCCESS);
}

void	builtins(t_cmd	*cmd)
{
	const char	*all_lowercase = lowercase(cmd->argv[0]);
	const int	argc = count_args(cmd->argv);
	int			exit_status;

	exit_status = -1;
	set_redir(cmd->redirects);
	if (ft_strnstr(all_lowercase, "cd", 2))
		exit_status = cd(argc, cmd->argv);
	else if (ft_strnstr(all_lowercase, "echo", 4))
		exit_status = echo(cmd->argv);
	else if (ft_strnstr(all_lowercase, "env", 3))
		env(argc);
	else if (ft_strnstr(all_lowercase, "exit", 4))
		exit_bash(argc, cmd);
	else if (ft_strnstr(all_lowercase, "export", 6))
		exit_status = export(argc, cmd->argv);
	else if (ft_strnstr(all_lowercase, "pwd", 3))
		pwd();
	if (exit_status != -1)
		set_last_process_exit_code(exit_status);
	ft_free_n_null((void **)&all_lowercase);
}
