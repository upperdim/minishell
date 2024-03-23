/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:39:22 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/23 19:10:10 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

/* Return whether string only consists of digits or not. */
static int	str_is_numeric(char *s)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	if (s == NULL || len < 1)
		return (0);
	if (s[0] == '-')
	{
		if (len == 1)
			return (0);
	}
	else if (!char_is_numeric(s[0]))
		return (0);
	i = 1;
	while (s[i] != '\0')
	{
		if (!char_is_numeric(s[i]))
			return (0);
		++i;
	}
	return (1);
}

void	exit_bash(char **input)
{
	// TODO: return input as unsigned char, let it overflow

	int		exit_code;
	char	*trimmed;
	
	ft_printf("exit\n");
	trimmed = ft_strtrim((*input) + 4, " ");
	if (ft_strlen(trimmed) == 0)
	{
		free(*input);
		free(trimmed);
		exit(0);
	}
	if (!str_is_numeric(trimmed))
	{
		char **splits = ft_split((*input) + 4, ' ');
		ft_printf("bash: exit: %s: numeric argument required\n", splits[1]);
		ft_free_2d_array((void ***)&splits, FREE_ANY_SIZE);
		free(*input);
		free(trimmed);
		exit(255);
	}
	
	
	exit_code = ft_atoi((*input) + 4);
	free(*input);
	free(trimmed);
	// ft_free_2d_array((void ***)&split);
	exit((unsigned char) exit_code);
}

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
