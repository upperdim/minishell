/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 12:50:49 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/18 21:40:36 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

void	ft_feedback(int error, t_instruction *result, char *exp_str)
{
	if (error == WRONG_CMD)
		ft_printf("\tCmd: %s\n\tExpected: echo\n", result->cmd);
	if (error == NO_ARGS)
		ft_printf("\tArgs: NULL\n\tExpected: args = %s\n", exp_str);
	if (error == WRONG_ARGS)
	{
		if (result->args && result->args[0])
			ft_printf("\tArgs[0]: %s\n\tExpected: %s\n", result->args[0],
				exp_str);
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

int	ft_check_output(t_instruction *result, char *exp_str)
{
	if (result)
	{
		if (ft_strncmp(result->cmd, "echo", ft_strlen(result->cmd)))
			return (WRONG_CMD);
		if (!result->args)
			return (NO_ARGS);
		if (ft_strncmp(*result->args, exp_str, ft_strlen(*result->args)))
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
		ft_printf("Test for parse_line(\"echo %s\"): PASS\n", exp_str);
		return (NO_ERROR);
	}
	return (NO_RESULT);
}

#if TEST == 4

int	main(void)
{
	t_instruction	*result;
	int				error;
	int				i;

	result = parse_line("echo \"Hello  World\"");
	error = ft_check_output(result, "Hello  World");
	if (error != NO_ERROR)
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"\"Hello  World\"");
		ft_feedback(error, result, "\"Hello  World\"");
	}
	if (result)
	{
		ft_free_n_null((void **)&result->cmd);
		i = 0;
		while (result->args && result->args[i])
			ft_free_n_null((void **)&result->args[i++]);
		ft_free_n_null((void **)&result->args);
		ft_free_n_null((void **)&result);
	}
	return (run_leaks("parse_line(\"echo \"Hello  World\"\")"), 0);
}

#elif TEST == 5

int	main(void)
{
	t_instruction	*result;
	int				error;
	int				i;

	result = parse_line("echo \"Hello' World\"");
	error = ft_check_output(result, "Hello' World");
	if (error != NO_ERROR)
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"\"Hello' World\"");
		ft_feedback(error, result, "\"Hello' World\"");
	}
	if (result)
	{
		ft_free_n_null((void **)&result->cmd);
		i = 0;
		while (result->args && result->args[i])
			ft_free_n_null((void **)&result->args[i++]);
		ft_free_n_null((void **)&result->args);
		ft_free_n_null((void **)&result);
	}
	return (run_leaks("parse_line(\"echo \"Hello' World\"\")"), 0);
}

#elif TEST == 6

int	main(void)
{
	t_instruction	*result;
	int				error;
	int				i;

	result = parse_line("echo \"Hello\" World\"");
	error = ft_check_output(result, "Hello\" World");
	if (error != NO_ERROR)
	{
		ft_printf("\nTest for parse_line(\"echo %s\"): Failed\n",
			"\"Hello\" World\"");
		ft_feedback(error, result, "\"Hello\" World\"");
	}
	if (result)
	{
		ft_free_n_null((void **)&result->cmd);
		i = 0;
		while (result->args && result->args[i])
			ft_free_n_null((void **)&result->args[i++]);
		ft_free_n_null((void **)&result->args);
		ft_free_n_null((void **)&result);
	}
	return (run_leaks("parse_line(\"echo \"Hello\" World\"\")"), 0);
}

#endif