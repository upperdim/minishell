/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:37:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/08 14:46:38 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	const char	*tmp = getcwd(NULL, 0);

	if (tmp)
		ft_printf("%s\n", tmp);
	else
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	ft_free_n_null((void **)&tmp);
	return (EXIT_SUCCESS);
}
