/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:03:42 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/13 11:18:09 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cd_test_1(int read_output_fd)
{
	char	*output;
	char	*prompt;

	output = get_test_input(read_output_fd);
	ft_free_n_null((void **)&output);
	output = get_test_input(read_output_fd);
	chdir(getenv("HOME"));
	prompt = get_prompt();
	print_feedback("Test 1 cd", output, prompt);
	ft_free_n_null((void **)&output);
	ft_free_n_null((void **)&prompt);
}
