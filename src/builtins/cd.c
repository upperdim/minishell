/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 14:32:03 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *input, t_mallocated *to_free)
{
	int	check;

	if (ft_strnstr(input, "cd", 2))
	{
		if (input[2])
			check = chdir(input + 3);
		else
			check = chdir(getenv("HOME"));
		errors((int [3]){check, 0, 0}, NULL, to_free);
	}
}
