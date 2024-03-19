/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:37:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/19 19:28:21 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *input, t_mallocated *to_free)
{
	char	*tmp;

	ft_printf("%s\n", tmp = getcwd(NULL, 0));
	check((int [3]){IF_NULL, 0, 0}, tmp, to_free);
	ft_free_n_null((void **)&tmp);
}
