/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:55:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 05:07:23 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 0 if `s` is NULL. */
static size_t	ft_strlen_nullcheck(const char *s)
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
   Return joint string of s1 and s2. Free s1.
   return NULL upon alloc error.
*/
char	*str_append(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*joint;

	len1 = ft_strlen_nullcheck(s1);
	len2 = ft_strlen_nullcheck(s2);
	if (len1 == 0 && len2 == 0)
		return (NULL);
	joint = (char *) malloc((len1 + len2 + 1) * sizeof(char));
	if (joint == NULL)
	{
		free((char *) s1);
		return (NULL);
	}
	i = -1;
	while (++i < len1)
		joint[i] = s1[i];
	i = -1;
	while (++i < len2)
		joint[len1 + i] = s2[i];
	joint[len1 + len2] = '\0';
	free((char *) s1);
	return (joint);
}

/*
   Return joint string of s1 and char_to_append. Free s1.
   return NULL upon alloc error.
*/
char	*str_appendc(char const *s1, char char_to_append)
{
	char	append[2];

	append[0] = char_to_append;
	append[1] = '\0';
	return (str_append(s1, append));
}
