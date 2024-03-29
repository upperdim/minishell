/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:26:18 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/29 18:35:07 by JFikents         ###   ########.fr       */
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

static void	leaks(void)
{
	system("\
if [ $(leaks test | grep -c \"LEAK\") != 0 ]; then\n\
	leaks test | grep -E \"Process |LEAK:|TOTAL\"\n\
	echo \"\x1b[1;31mFailed leak test in test\"\n\
fi");
}

int	main(void)
{
	atexit(leaks);
	compile_minishell();
	unlink("logs/minishell_builtins.log");
	test_1_builtins();
	return (0);
}
