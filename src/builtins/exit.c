/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:39:22 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/20 15:46:05 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_bash(const int argc, t_cmd	*cmd)
{
	extern int	errno;

	ft_printf("exit\n");
	if (argc > 2 && str_is_numeric(cmd->argv[1]))
	{
		errno = 1;
		ft_printf_fd(2, ERROR_MSG, "exit", "too many arguments");
		return (EXIT_FAILURE);
	}
	if (argc == 2 && str_is_numeric(cmd->argv[1]))
		errno = ft_atoi(cmd->argv[1]);
	else if (argc == 2)
	{
		errno = 255;
		ft_printf_fd(2, ERROR_MSG_PERROR"%s: %s\n", "exit", cmd->argv[1],
			"numeric argument required");
	}
	if (cmd)
		free_cmd((t_cmd **)&cmd);
	clean_up();
	exit((unsigned char)errno);
}
// exit is unsigned char, so it can only be 0-255

// Test "exit      " should return 0. strlen check shouldn't fail)
// Test "exit -1" should return 255, it should overflow unsigned char)

// bash-3.2$ exit 123x123
// exit
// bash: exit: 123x123: numeric argument required

// bash-3.2$ exit     123x123      52    
// exit
// bash: exit: 123x123: numeric argument required

// bash-3.2$ exit     123123      52    
// exit
// bash: exit: too many arguments
// DOESN'T EXIT BASH!
