/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:08:41 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/15 16:45:48 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	full_free(t_mallocated *mallocated)
{
	t_mallocated	*tmp;

	while (mallocated)
	{
		tmp = mallocated->next;
		ft_free_n_null(&mallocated->ptr);
		ft_free_n_null((void **)&mallocated);
		mallocated = tmp;
	}
}

void	errors(int check[3], void *if_null, t_mallocated *mallocated)
{
	extern int	errno;

	if (check[STATUS] == -1 || (check[STATUS] == IF_NULL && !if_null))
	{
		ft_putstr_fd("minishell: ", 2);
		perror(NULL);
		full_free(mallocated);
		exit(errno);
	}
}
		// ft_putstr_fd(get_where(check), 2);
		// ft_putstr_fd(get_instruction(check), 2);
