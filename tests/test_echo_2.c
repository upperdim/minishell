/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:17:20 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 14:30:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void echo_test_6(int read_output_fd)
{
	char	*output;

	output = get_next_line(read_output_fd);
	ft_free_n_null((void **)&output);
	output = get_next_line(read_output_fd);
	print_feedback("Test 6 echo", output, "Hello World -n");
	ft_free_n_null((void **)&output);
}
