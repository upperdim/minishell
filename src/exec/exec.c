/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/06 19:18:52 by JFikents         ###   ########.fr       */
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

char	**transform_to_array(t_token *token)
{
	char	**argv;
	int		argc;

	argc = 0;
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
	char	**argv;
	int		pipe_fd[2];

	argv = transform_to_array(token);
	if (argv == NULL)
		return (1);
	(void)argv;
	(void)pipe_fd;
	return (0);
}
