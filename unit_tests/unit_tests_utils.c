/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:03:36 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/19 12:52:13 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_parser.h"

#ifdef __APPLE__

void	run_leaks(const char *test_name)
{
	int	is_there_leaks;

	is_there_leaks = system("\
if [ $(leaks a.out | grep \"leaks for \" | awk '{print $3}') != 0 ]; then\n\
	leaks a.out | grep \"Process \">> logs/result_parser.log\n\
exit 1\n\
fi\n\
exit 0");
	if (is_there_leaks)
		ft_printf("Failed leak test in %s", test_name);
}
#else

void	run_leaks(const char *test_name)
{
	(void)test_name;
	return ;
}
#endif

void	ft_free_results(t_instruction **result)
{
	int	i;

	ft_free_n_null((void **)&((*result)->cmd));
	i = 0;
	while ((*result)->args && (*result)->args[i])
		ft_free_n_null((void **)&((*result)->args[i++]));
	ft_free_n_null((void **)(&(*result)->args));
	ft_free_n_null((void **)result);
}

void	ft_feedback(int error, t_instruction *result, const char **exp_str)
{
	int	i;

	i = -1;
	if (error == WRONG_CMD)
		ft_printf("\tCmd: %s\n\tExpected: echo\n", result->cmd);
	if (error == NO_ARGS)
		ft_printf("\tArgs: NULL\n\tExpected: args = %s\n", exp_str[0]);
	if (error == WRONG_ARGS)
		while (result->args && result->args[++i] && exp_str[i])
			ft_printf("\tArgs[%i]: %s\n\tExpected: %s\n", i, result->args[i],
				exp_str[i]);
	if (error == WRONG_ARGS && (result->args[i] || exp_str[i]))
		ft_printf("\tMore/Less args than expected\n", result->args[i]);
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

int	ft_check_output(t_instruction *token, const char **expect)
{
	int	i;

	i = -1;
	if (!token)
		return (NO_RESULT);
	if (ft_strncmp(token->cmd, "echo", ft_strlen(token->cmd)))
		return (WRONG_CMD);
	if (!token->args)
		return (NO_ARGS);
	while (token->args[++i] && expect[i])
		if (ft_strncmp(token->args[i], expect[i], ft_strlen(expect[i]) + 1))
			return (WRONG_ARGS);
	if (token->args[i] || expect[i])
		return (WRONG_ARGS);
	if (token->and_index != 0)
		return (WRONG_AND_INDEX);
	if (token->next != NULL)
		return (WRONG_NEXT);
	if (token->flags.pipe_in != -1)
		return (WRONG_PIPE_IN);
	if (token->flags.pipe_out != -1)
		return (WRONG_PIPE_OUT);
	if (token->flags.redir != 0)
		return (WRONG_REDIR);
	return (NO_ERROR);
}
