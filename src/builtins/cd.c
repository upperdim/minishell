/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/19 19:27:00 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char *input, t_mallocated *to_free)
{
	int	status;

	if (input[0])
		status = chdir(input);
	else
		status = chdir(getenv("HOME"));
	check((int [3]){status, 0, 0}, NULL, to_free);
}
