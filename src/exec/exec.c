/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/30 14:15:44 by JFikents         ###   ########.fr       */
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

void	print_test(void)
{
	int			i;

	i = 0;
	ft_putstr_fd(getenv("MINISHELL_ENV"), 1);
}

void	ft_free_environ(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		free(environ[i]);
		i++;
	}
	free(environ);
}

int	main(void)
{
	extern char	**environ;
	char		**new_environ;
	int			env_count;

	env_count = 0;
	while (environ[env_count])
		env_count++;
	new_environ = ft_calloc(env_count + 2, sizeof(char *));
	if (!new_environ)
		return (1);
	env_count = 0;
	while (environ[env_count])
	{
		new_environ[env_count] = ft_strdup(environ[env_count]);
		if (!new_environ[env_count])
			return (1);
		env_count++;
	}
	new_environ[env_count] = ft_strdup("MINISHELL_ENV=TRUE");
	if (!new_environ[env_count])
		return (1);
	environ = new_environ;
	print_test();
	return (0);
}
