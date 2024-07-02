/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/02 19:34:45 by JFikents         ###   ########.fr       */
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

void	builtins(t_cmd	*cmd)
{
	const char	*all_lowercase = lowercase(cmd->argv[0]);
	const int	argc = count_args(cmd->argv);
	int			exit_status;
	char		*var_exit_code;
	char		*exit_code;

	set_redir(cmd->redirects);
	if (ft_strnstr(all_lowercase, "cd", 2))
		cd(argc, cmd->argv);
	else if (ft_strnstr(all_lowercase, "echo", 4))
		echo(cmd->argv);
	else if (ft_strnstr(all_lowercase, "env", 3))
		env(argc);
	else if (ft_strnstr(all_lowercase, "exit", 4))
		exit_bash(argc, cmd);
	else if (ft_strnstr(all_lowercase, "export", 6))
		exit_status = export(argc, cmd->argv);
	else if (ft_strnstr(all_lowercase, "pwd", 3))
		pwd();
	exit_code = ft_itoa(exit_status);
	var_exit_code = ft_strjoin("LAST_PROCESS_EXIT_CODE=", exit_code);
	add_env_var(var_exit_code);
	ft_free_n_null((void **)&exit_code);
	ft_free_n_null((void **)&var_exit_code);
	ft_free_n_null((void **)&all_lowercase);
}
// {
// 	char	*trimmed_input;

// 	trimmed_input = ft_strtrim(input, " ");
// 	if (ft_strlen(trimmed_input) != ft_strlen(input))
// 		input = trimmed_input;
// 	if (ft_strnstr(input, "cd", 2))
// 		cd(input + 2);
// 	else if (ft_strnstr(input, "echo", 4))
// 		echo(input + 4);
// 	else if (ft_strnstr(input, "env", 3))
// 		env(input + 3);
// 	else if (ft_strnstr(input, "exit", 4))
// 		exit_bash(&input);
// 	// export(input, to_free); Not implemented yet
// 	else if (ft_strnstr(input, "pwd", 3))
// 		pwd();
// 	// unset(input, to_free); Not implemented yet
// 	ft_free_n_null((void **)&trimmed_input);
// }
