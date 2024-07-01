/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:37:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/01 18:11:56 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	const char	*tmp = getcwd(NULL, 0);

	if (tmp)
		ft_printf("%s\n", tmp);
	else
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		perror(NULL);
	}
	ft_free_n_null((void **)&tmp);
}
