/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:39:22 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/01 18:09:04 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Return whether string only consists of digits or not. */
static int	str_is_numeric(char *str)
{
	size_t			i;
	const size_t	len = ft_strlen(str);

	if (str == NULL || len == 0)
		return (0);
	i = 0;
	if (str[i] == '-')
	{
		if (len == 1)
			return (0);
		i ++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		++i;
	return (i);
}

void	exit_bash(t_cmd	*cmd)
{
	extern int	errno;
	const int	argc = count_args(cmd->argv);

	ft_printf("exit\n");
	if (argc > 2 && str_is_numeric(cmd->argv[1]))
	{
		errno = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	if (argc == 2 && str_is_numeric(cmd->argv[1]))
		errno = ft_atoi(cmd->argv[1]);
	else if (argc == 2)
	{
		errno = 2;
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			cmd->argv[1]);
	}
	while (cmd->prev != NULL)
		cmd = cmd->prev;
	free_cmd(cmd);
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
