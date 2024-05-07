/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:45:26 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/07 12:32:17 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdlib.h>

#ifndef TEST

int	main(void)
{
	t_instruction	*result;

	result = parse_line("");
	if (result)
	{
		ft_printf("\nTest for parse_line(\"\"): Failed\n");
		ft_printf("Outputs: %p\nExpected: NULL\n", result);
		free(result);
		result = NULL;
	}
	system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
	echo \"Failed leak test in parse_line(\\\"\\\")\" >> logs/result_parser.log\n\
fi");
	return (0);
}
#elif TEST == 1

int	main(void)
{
	t_instruction	*result;

	result = parse_line(NULL);
	if (result)
	{
		ft_printf("\nTest for parse_line(NULL): Failed\n");
		ft_printf("Outputs: %p\nExpected: NULL\n", result);
		free(result);
		result = NULL;
	}
	system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
	echo \"Failed leak test in parse_line(NULL)\" >> logs/result_parser.log\n\
fi");
	return (0);
}
#endif
