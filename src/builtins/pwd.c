/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:37:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 14:32:55 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char *input, t_mallocated *to_free)
{
	char	*tmp;

	if (ft_strnstr(input, "pwd", 3))
	{
		ft_printf("%s\n", tmp = getcwd(NULL, 0));
		errors((int [3]){IF_NULL, 0, 0}, tmp, to_free);
		ft_free_n_null((void **)&tmp);
	}
}
