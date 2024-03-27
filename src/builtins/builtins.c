/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 13:23:04 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// temp code until we are certain about `input`
	// to do processing of the raw input read from the user
void	builtins(char *input)
{
	char	*trimmed_input;

	trimmed_input = ft_strtrim(input, " ");
	if (ft_strlen(trimmed_input) == ft_strlen(input))
		ft_free_n_null((void **)&trimmed_input);
	else
	{
		ft_free_n_null((void **)&input);
		input = trimmed_input;
	}
	if (ft_strnstr(input, "cd", 2))
		cd(input + 2);
	else if (ft_strnstr(input, "echo", 4))
		echo(input + 4);
	else if (ft_strnstr(input, "env", 3))
		env(input + 3);
	else if (ft_strnstr(input, "exit", 4))
		exit_bash(&input);
	// export(input, to_free); Not implemented yet
	else if (ft_strnstr(input, "pwd", 3))
		pwd();
	// unset(input, to_free); Not implemented yet
}
