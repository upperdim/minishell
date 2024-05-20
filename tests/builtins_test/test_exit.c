/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:03:55 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 15:24:26 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	exit_test_1(int read_output_fd, int status)
{
	char	*output;
	char	*secundary_output;
	char	*str_exit_status;

	output = get_next_line(read_output_fd);
	secundary_output = get_next_line(read_output_fd);
	while (output && secundary_output && *output && *secundary_output)
	{
		ft_free_n_null((void **)&output);
		output = get_next_line(read_output_fd);
		if (!output || !*output)
			break ;
		ft_free_n_null((void **)&secundary_output);
		secundary_output = get_next_line(read_output_fd);
	}
	if (!output || !*output)
	{
		ft_free_n_null((void **)&output);
		output = secundary_output;
	}
	print_feedback("Test 1 exit", output, "exit");
	ft_free_n_null((void **)&output);
	str_exit_status = ft_itoa(WEXITSTATUS(status));
	print_feedback("Test 1 exit status", str_exit_status, "255");
	ft_free_n_null((void **)&str_exit_status);
}
