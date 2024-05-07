/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 17:45:26 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/07 14:29:59 by JFikents         ###   ########.fr       */
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
	else
		ft_printf("Test for parse_line(\"\"): PASS\n");
	system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
	echo \"Failed leak test in parse_line(\\\"\\\")\" >> logs/result_parser.log\n\
fi");
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
	system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
	echo \"Failed leak test in parse_line(NULL)\" >> logs/result_parser.log\n\
fi");
	return (0);
}
#elif TEST == 3

enum e_error_type
{
	NO_ERROR,
	NO_RESULT,
	WRONG_CMD,
	NO_ARGS,
	WRONG_ARGS,
	WRONG_AND_INDEX,
	WRONG_NEXT,
	WRONG_PIPE_IN,
	WRONG_PIPE_OUT,
	WRONG_REDIR
};

int	ft_check_output(t_instruction *result)
{
	if (result)
	{
		if (ft_strncmp(result->cmd, "echo", ft_strlen(result->cmd)))
			return (WRONG_CMD);
		if (!result->args)
			return (NO_ARGS);
		if (ft_strncmp(result->args[0], "Hello", ft_strlen(result->args[0])))
			return (WRONG_ARGS);
		if (!result->args[1]
			|| ft_strncmp(result->args[1], "World", ft_strlen(result->args[1])))
			return (WRONG_ARGS);
		if (result->and_index != 0)
			return (WRONG_AND_INDEX);
		if (result->next != NULL)
			return (WRONG_NEXT);
		if (result->flags.pipe_in != -1)
			return (WRONG_PIPE_IN);
		if (result->flags.pipe_out != -1)
			return (WRONG_PIPE_OUT);
		if (result->flags.redir != 0)
			return (WRONG_REDIR);
		ft_printf("Test for parse_line(\"echo Hello World\"): PASS\n");
		return (NO_ERROR);
	}
	return (NO_RESULT);
}

void	ft_feedback(int error, t_instruction *result)
{
	if (error == WRONG_CMD)
		ft_printf("\tCmd: %s\n\tExpected: echo\n", result->cmd);
	if (error == NO_ARGS)
		ft_printf("\tArgs: NULL\n\tExpected: args = {\"Hello\", \"World\"}\n");
	if (error == WRONG_ARGS)
	{
		if (result->args && result->args[0])
			ft_printf("\tArgs[0]: %s\n\tExpected: Hello\n", result->args[0]);
		if (result->args && result->args[1])
			ft_printf("\tArgs[1]: %s\n\tExpected: World\n", result->args[1]);
	}
	if (error == WRONG_AND_INDEX)
		ft_printf("\tAnd Index: %d\n\tExpected: 0\n", result->and_index);
	if (error == WRONG_NEXT)
		ft_printf("\tNext: %p\n\tExpected: NULL\n", result->next);
	if (error == WRONG_PIPE_IN)
		ft_printf("\tPipe In: %d\n\tExpected: -1\n", result->flags.pipe_in);
	if (error == WRONG_PIPE_OUT)
		ft_printf("\tPipe Out: %d\n\tExpected: -1\n", result->flags.pipe_out);
	if (error == WRONG_REDIR)
		ft_printf("\tRedir: %d\n\tExpected: 0\n", result->flags.redir);
	if (error == NO_RESULT)
		ft_printf("Output: NULL\nExpected: t_instruction\n");
}

int	main(void)
{
	t_instruction	*result;
	int				error;

	result = parse_line("echo Hello World");
	error = ft_check_output(result);
	if (error != NO_ERROR)
	{
		ft_printf("\nTest for parse_line(\"echo Hello World\"): Failed\n");
		ft_feedback(error, result);
		if (result)
			free(result);
		result = NULL;
	}
	system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
	echo \"Failed leak test in parse_line(\"echo Hello World\")\" >> logs/result_parser.log\n\
fi");
	return (0);
}

#endif