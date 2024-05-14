/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/14 13:15:57 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

#ifdef __APPLE__

void	run_leaks(char *test_name)
{
	int	is_there_leaks;

	is_there_leaks = system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
exit 1\n\
fi\n\
exit 0");
	if (is_there_leaks == TRUE)
		ft_printf("Failed leak test in %s", test_name);
}
#else

void	run_leaks(char *test_name)
{
	(void)test_name;
	return ;
}

#endif