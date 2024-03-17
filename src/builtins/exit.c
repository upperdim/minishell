/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:55:06 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 18:56:15 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_bash(char *input, t_mallocated *to_free)
{
	if (ft_strnstr(input, "exit", 4))
		check((int [3]){EXIT, 0, 0}, NULL, to_free);
}
