/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 20:28:38 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *input, t_alloc_list *to_free)
{
	if (ft_strnstr(input, "cd", 2))
		cd(input + 2);
	else if (ft_strnstr(input, "echo", 4))
		echo(input + 4);
	else if (ft_strnstr(input, "env", 3))
		env(input + 3);
	else if (ft_strnstr(input, "exit", 4))
		exit_bash(to_free);
	// export(input, to_free); Not implemented yet
	else if (ft_strnstr(input, "pwd", 3))
		pwd();
	// unset(input, to_free); Not implemented yet
}
