/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 19:35:44 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *input, t_mallocated *to_free)
{
	int	status;

	if (ft_strnstr(input, "cd", 2))
	{
		if (input[2])
			status = chdir(input + 3);
		else
			status = chdir(getenv("HOME"));
		check((int [3]){status, 0, 0}, NULL, to_free);
	}
}
