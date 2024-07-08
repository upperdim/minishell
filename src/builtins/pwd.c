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
	const char	*cwd = getcwd(NULL, 0);

	if (cwd != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		ft_printf_fd(2, ERROR_MSG_PERROR, "pwd");
		perror(NULL);
		return (EXIT_FAILURE);
	}
	ft_free_n_null((void **)&cwd);
	return (EXIT_SUCCESS);
}
