/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:26:18 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/29 13:03:32 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	compile_minishell(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (!pid)
		ft_execve((char *[]){check_for_cmd("make"), "re", "COLOR=0", NULL},
			NULL, NULL);
	waitpid(pid, NULL, 0);
}

int	main(void)
{
	compile_minishell();
	unlink("logs/minishell_builtins.log");
	test_1_builtins();
	system("leaks test");
	return (0);
}
