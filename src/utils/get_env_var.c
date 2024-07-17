/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:29:43 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 20:03:02 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Return value of environment variable `var_name`, 
	return an empty string if not found.
*/
char	*get_env_var(char *var_name)
{
	extern char	**environ;
	int			equals_symbol_idx;
	int			last_idx;
	int			i;
	
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], var_name, ft_strlen(var_name)) == 0)
		{
			equals_symbol_idx = find_idx_of_nextc(environ[i], 0, '=');
			if (equals_symbol_idx == -1)
				break ;
			last_idx = ft_strlen(environ[i]) - 1;
			return (str_sub(environ[i], equals_symbol_idx + 1, last_idx));
		}
		++i;
	}
	return (ft_strdup(""));
}
