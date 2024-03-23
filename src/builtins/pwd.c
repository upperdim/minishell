/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:37:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 18:09:05 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*tmp;

	ft_printf("%s\n", tmp = getcwd(NULL, 0));
	if (!tmp)
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		perror(NULL);
		ft_putstr_fd("\n", 2);
	}
	ft_free_n_null((void **)&tmp);
}
