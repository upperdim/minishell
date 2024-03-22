/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:08:41 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 15:58:29 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_alloc_list *mallocated)
{
	free_all_list(mallocated);
	rl_clear_history();
	system("leaks minishell");
	exit(0);
}
		// ft_putstr_fd(get_where(check), 2);
		// ft_putstr_fd(get_instruction(check), 2);
