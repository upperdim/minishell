/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:55:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 06:26:28 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 0 if `s` is NULL. */
int	strlen_null(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}

/*
	Return a substring of `s` from `start_idx` to `end_idx` INCLUSIVE.
	Uses allocation so return string must be freed by the caller.
	TODO: clean and exit upon alloc error.
*/
char	*str_sub(char *s, int start_idx, int end_idx)
{
	return (ft_substr(s, start_idx, end_idx - start_idx + 1));
}

/*
	Search `search_char` in `s` starting from index `search_start_idx`.
	Return -1 if not found
*/
int	find_idx_of_nextc(char *s, int search_start_idx, char search_char)
{
	int	i;

	i = search_start_idx;
	while (s[i] != '\0')
	{
		if (s[i] == search_char)
			return (i);
		++i;
	}
	return (-1);
}
