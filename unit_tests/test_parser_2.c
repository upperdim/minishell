/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:50:49 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/19 12:36:02 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

#if TEST == 6

int	main(void)
{
	t_instruction	*result;
	int				error;

	result = parse_line("echo \"Hello\" World\"");
	error = ft_check_output(result, (char *[3]){"Hello", "World\"", NULL});
	if (error == NO_ERROR)
		ft_printf("Test for parse_line(\"echo \"Hello\" World\"\"): PASS\n");
	else
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"\"Hello\" World\"");
		ft_feedback(error, result, (char *[3]){"Hello", "World\"", NULL});
	}
	if (result)
		ft_free_results(&result);
	return (run_leaks("parse_line(\"echo \"Hello\" World\"\")"), 0);
}

#elif TEST == 7

int	main(void)
{
	t_instruction	*result;
	int				error;

	result = parse_line("echo Hello\" World");
	error = ft_check_output(result, (char *[3]){"Hello\"", "World", NULL});
	if (error == NO_ERROR)
		ft_printf("Test for parse_line(\"echo Hello\" World\"): PASS\n");
	else
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"Hello\" World");
		ft_feedback(error, result, (char *[3]){"Hello\"", "World", NULL});
	}
	if (result)
		ft_free_results(&result);
	return (run_leaks("parse_line(\"echo Hello\" World\")"), 0);
}

#endif