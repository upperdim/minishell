/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:39:22 by tunsal            #+#    #+#             */
/*   Updated: 2024/09/14 20:26:14 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_in_llong_range(const char *str)
{
	const int	str_len = ft_strlen(str);
	int			is_negative;
	const char	*ll_max = "9223372036854775807";
	const char	*ll_min = "9223372036854775808";

	is_negative = 0;
	if (str == NULL)
		return (false);
	if (str[0] == '-')
	{
		is_negative = 1;
		str++;
	}
	if (str_len + is_negative < 19)
		return (true);
	if (is_negative == false && str_len == 19
		&& ft_strncmp(str, ll_max, str_len) <= 0)
		return (true);
	if (is_negative == true && str_len == 19 + is_negative
		&& ft_strncmp(str, ll_min, str_len) <= 0)
		return (true);
	return (false);
}

int	exit_bash(const int argc, t_cmd	*cmd)
{
	extern int	errno;
	bool		is_numeric;

	is_numeric = false;
	if (cmd != NULL)
		is_numeric = str_is_numeric(cmd->argv[1])
			& is_in_llong_range(cmd->argv[1]);
	ft_printf("exit\n");
	if (argc > 2 && is_numeric)
	{
		errno = 1;
		return (ft_printf_fd(2, ERROR_MSG, "exit", "too many arguments"), 1);
	}
	if (argc == 2 && is_numeric)
		errno = ft_atoi(cmd->argv[1]);
	else if (argc == 2 || (is_numeric == false && argc > 2))
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
