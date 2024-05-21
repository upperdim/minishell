/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 12:26:18 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/21 13:14:14 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
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

#if __APPLE__

void	ft_check_minishell_builtins_leaks(void)
{
	system("if [ $(leaks minishell_builtins | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks minishell_builtins | grep -E \"Process |LEAK:|TOTAL\"\n\
	echo \"\x1b[1;31mFailed leak test in minishell_builtins\"\n\
fi");
}
#else

void	ft_check_minishell_builtins_leaks(void)
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
