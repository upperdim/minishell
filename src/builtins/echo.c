/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 20:14:05 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*echo_parser(char *input)
{
	char	*parsed_input;
	int		i;

	i = 0;
	parsed_input = input;
	if (parsed_input[0] == '-')
	{
		i++;
		while (parsed_input[i] == 'n')
			i++;
		if (parsed_input[i] == ' ' || parsed_input[i] == '\0')
			parsed_input += i;
	}
	if (parsed_input != input)
		while (*parsed_input == ' ')
			parsed_input++;
	return (parsed_input);
}

void	echo(char *input)
{
	int		space_is_present;
	char	*parsed_input;
	int		flag_n;

	space_is_present = 0;
	flag_n = 0;
	while (*input == ' ')
	{
		input++;
		space_is_present = 1;
	}
	parsed_input = echo_parser(input);
	if (parsed_input != input && ++flag_n)
		input = parsed_input;
	if (*input && space_is_present)
		ft_putstr_fd(input, 1);
	else if (*input)
	{
		ft_putstr_fd("minishell: echo", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": command not found", 2);
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}
