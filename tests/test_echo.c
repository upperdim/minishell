/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:01:31 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 14:16:50 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	echo_test_1(int read_output_fd)
{
	char	*output;

	output = get_next_line(read_output_fd);
	ft_free_n_null((void **)&output);
	output = get_next_line(read_output_fd);
	if (ft_strncmp(output, "Hello World\n", ft_strlen("Hello World\n")))
		print_feedback("Test 1 echo", output, "Hello World\n");
	else
		ft_putendl_fd(GREEN"Test 1 echo success", 1);
	ft_free_n_null((void **)&output);
}

void	echo_test_2(int read_output_fd)
{
	char	*output;

	output = get_next_line(read_output_fd);
	ft_free_n_null((void **)&output);
	output = get_next_line(read_output_fd);
	if (ft_strncmp(output, "-nnnnnnnnnm Hello World", ft_strlen("-nnnnnnnnnm Hello World")))
		print_feedback("Test 2 echo", output, "-nnnnnnnnnm Hello World");
	else
		ft_putendl_fd(GREEN"Test 2 echo success", 1);
	ft_free_n_null((void **)&output);
}

void	echo_test_3(int read_output_fd)
{
	char	*output;
	char	*prompt;
	char	*echo_line;

	output = get_next_line(read_output_fd);
	ft_free_n_null((void **)&output);
	output = get_next_line(read_output_fd);
	prompt = get_prompt();
	echo_line = ft_strjoin("Hello World", prompt);
	ft_free_n_null((void **)&prompt);
	if (ft_strncmp(output, echo_line, ft_strlen(echo_line)))
		print_feedback("Test 3 echo", output, echo_line);
	else
		ft_putendl_fd(GREEN"Test 3 echo success", 1);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&echo_line);
}

void	echo_test_4(int read_output_fd)
{
	char	*output;
	char	*prompt;
	char	*echo_line;

	output = get_next_line(read_output_fd);
	prompt = get_prompt();
	echo_line = ft_strjoin("Hello World", prompt);
	ft_free_n_null((void **)&prompt);
	if (ft_strncmp(output, echo_line, ft_strlen(echo_line)))
		print_feedback("Test 4 echo", output, echo_line);
	else
		ft_putendl_fd(GREEN"Test 4 echo success", 1);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&echo_line);
}

void	echo_test_5(int read_output_fd)
{
	char	*output;

	output = get_next_line(read_output_fd);
	if (ft_strncmp(output, "Hello World-n", ft_strlen("Hello World-n")))
		print_feedback("Test 5 echo", output, "Hello World-n");
	else
		ft_putendl_fd(GREEN"Test 5 echo success", 1);
	ft_free_n_null((void **)&output);
}
