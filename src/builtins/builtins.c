/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:52:34 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 15:32:57 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins(char *input, t_mallocated *to_free)
{
	cd(input, to_free);
	echo(input);
	env(input);
	exit_bash(input, to_free);
	// export(input, to_free); Not implemented yet
	pwd(input, to_free);
	// unset(input, to_free); Not implemented yet
}
