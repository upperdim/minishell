/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 09:08:15 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 09:08:48 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	s_isspace3(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

/* Parse a long from a string and return it. */
long	ft_atol(const char *str)
{
	int				sign;
	long			result;
	unsigned int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (s_isspace3(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		++i;
	}
	else if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0') % 10;
		i++;
	}
	return (result * sign);
}
