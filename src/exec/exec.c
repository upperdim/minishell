/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:01:28 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 20:34:07 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(char *cmd, char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		check(&pid, "Error forking", NULL);
	if (pid == 0)
	{
		execve(cmd, argv, NULL);
		check(&pid, "Error execve", NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
}
