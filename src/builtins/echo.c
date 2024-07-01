/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:57:51 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/01 15:53:05 by JFikents         ###   ########.fr       */
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

static int	check_for_n_flag(char **input)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	if (ft_strncmp(input[1], "-n", 2) == 0)
	{
		i = 2;
		while (input[1][i++] == 'n')
			flag_n = 1;
		if (input[1][i] != '\0')
			return (0);
	}
	return (flag_n);
}

void	echo(char **input)
{
	int			i;
	const int	flag_n = check_for_n_flag(input);


	i = flag_n;
	while (input[++i])
	{
		if (i > 1 + flag_n)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(input[i], 1);
	}
	if (!flag_n)
		ft_putstr_fd("\n", 1);
}
// {
// 	int		space_is_present;
// 	char	*parsed_input;
// 	int		flag_n;

// 	space_is_present = 0;
// 	flag_n = 0;
// 	while (*input == ' ')
// 	{
// 		input++;
// 		space_is_present = 1;
// 	}
// 	parsed_input = echo_parser(input);
// 	if (parsed_input != input && ++flag_n)
// 		input = parsed_input;
// 	if (*input && space_is_present)
// 		ft_putstr_fd(input, 1);
// 	else if (*input)
// 		ft_printf_fd(2, "minishell: echo%s: command not found", input);
// 	if (!flag_n)
// 		ft_putstr_fd("\n", 1);
// }