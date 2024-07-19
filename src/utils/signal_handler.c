/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:24:27 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/19 17:30:32 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	interactive_mode_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		ft_printf("\n");
		rl_redisplay();
	}
	return ;
}

static void	execution_signal_handler(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n");
	if (sig == SIGQUIT)
		ft_printf_fd(2, "Quit: 3\n");
}

void	set_signal_handlers_mode(enum e_signal_mode mode)
{
	if (mode == EXECUTION)
	{
		signal(SIGINT, execution_signal_handler);
		signal(SIGQUIT, execution_signal_handler);
	}
	else if (mode == INTERACTIVE)
	{
		signal(SIGINT, interactive_mode_signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
