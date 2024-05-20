/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:26:18 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/20 15:56:13 by JFikents         ###   ########.fr       */
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
		ft_execve((char *[]){check_for_cmd("make"), "-s", "re", "COLOR=0",
			NULL}, NULL, NULL);
	waitpid(pid, NULL, 0);
}

#ifdef __APPLE__

static void	leaks(void)
{
	system("\
if [ $(leaks test | grep -c \"LEAK\") != 0 ]; then\n\
	leaks test | grep -E \"Process |LEAK:|TOTAL\"\n\
	echo \"\x1b[1;31mFailed leak test in test\x1b[0m\"\n\
fi");
}
#else

static void	leaks(void)
{
	return ;
}
#endif

int	main(void)
{
	atexit(leaks);
	compile_minishell();
	unlink("tests/logs/minishell_builtins.log");
	test_1_builtins();
	return (0);
}
