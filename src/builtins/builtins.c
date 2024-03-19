/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/19 19:28:32 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *input, t_mallocated *to_free)
{
	if (ft_strnstr(input, "cd", 2))
		cd(input + 2, to_free);
	else if (ft_strnstr(input, "echo ", 5))
		echo(input + 4);
	else if (ft_strnstr(input, "env", 3))
		env(input);
	else if (ft_strnstr(input, "exit", 4))
		exit_bash(input, to_free);
	// export(input, to_free); Not implemented yet
	else if (ft_strnstr(input, "pwd", 3))
		pwd(input, to_free);
	// unset(input, to_free); Not implemented yet
}
