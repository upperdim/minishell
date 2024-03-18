/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:08:41 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 19:28:01 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_perror(int error_code)
{
	if (error_code == UNKNOWN_COMMAND)
		ft_putstr_fd("command not found", 2);
	if (error_code == EPIPE)
		ft_putstr_fd("unable to create pipe", 2);
}

void	check(int check[3], void *if_null, t_mallocated *mallocated)
{
	extern int	errno;

	if (check[STATUS] == -1 || (check[STATUS] == IF_NULL && !if_null))
	{
		ft_putstr_fd("minishell: ", 2);
		if (!check[ERROR])
			perror(NULL);
		else
			ft_perror(check[ERROR]);
		full_free(mallocated);
		rl_clear_history();
		system("leaks minishell");
		if (check[ERROR])
			exit(check[ERROR]);
		exit(errno);
	}
	else if (check[STATUS] == EXIT)
	{
		full_free(mallocated);
		rl_clear_history();
		system("leaks minishell");
		exit(0);
	}
}
		// ft_putstr_fd(get_where(check), 2);
		// ft_putstr_fd(get_instruction(check), 2);
