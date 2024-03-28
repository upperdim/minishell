/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 15:03:42 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/28 15:04:23 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cd_test_1(int read_output_fd)
{
	char	*output;
	char	*secundary_output;

	if (!output || !*output)
	{
		ft_free_n_null((void **)&output);
		output = secundary_output;
	}
	print_feedback("Test 1 cd", output, "cd");
	ft_free_n_null((void **)&output);
}