/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:55:06 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/19 19:28:48 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_bash(char *input, t_mallocated *to_free)
{
	(void)input;
	check((int [3]){EXIT, 0, 0}, NULL, to_free);
}
