/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:45:26 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/19 12:36:27 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

#if TEST == 1

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
	else
		ft_printf("Test for parse_line(\"\"): PASS\n");
	run_leaks("parse_line(\"\")");
	return (0);
}
#elif TEST == 2

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
	else
		ft_printf("Test for parse_line(NULL): PASS\n");
	run_leaks("parse_line(NULL)");
	return (0);
}
#elif TEST == 3

int	main(void)
{
	t_instruction	*result;
	int				error;

	result = parse_line("echo Hello World");
	error = ft_check_output(result, (char *[3]){"Hello", "World", NULL});
	if (error != NO_ERROR)
	{
		ft_printf("\nTest for parse_line(\"echo Hello World\"): Failed\n");
		ft_feedback(error, result, (char *[3]){"Hello", "World", NULL});
	}
	if (result)
		ft_free_results(&result);
	return (run_leaks("parse_line(\"echo Hello World\")"), 0);
}

#elif TEST == 4

int	main(void)
{
	t_instruction	*result;
	int				error;

	result = parse_line("echo \"Hello  World\"");
	error = ft_check_output(result, (char *[2]){"Hello  World", NULL});
	if (error == NO_ERROR)
		ft_printf("Test for parse_line(\"echo \"Hello  World\"\"): PASS\n");
	else
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"\"Hello  World\"");
		ft_feedback(error, result, (char *[2]){"\"Hello  World\"", NULL});
	}
	if (result)
		ft_free_results(&result);
	return (run_leaks("parse_line(\"echo \"Hello  World\"\")"), 0);
}

#elif TEST == 5

int	main(void)
{
	t_instruction	*result;
	int				error;

	result = parse_line("echo \"Hello' World\"");
	error = ft_check_output(result, (char *[2]){"Hello' World", NULL});
	if (error == NO_ERROR)
		ft_printf("Test for parse_line(\"echo \"Hello' World\"\"): PASS\n");
	else
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"\"Hello' World\"");
		ft_feedback(error, result, (char *[2]){"\"Hello' World\"", NULL});
	}
	if (result)
		ft_free_results(&result);
	return (run_leaks("parse_line(\"echo \"Hello' World\"\")"), 0);
}

#endif