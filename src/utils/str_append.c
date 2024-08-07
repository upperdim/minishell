/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:26:39 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 07:30:53 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Return joint string of s1 and s2. Free s1.
   return NULL upon alloc error.
*/
static char	*str_join_free(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*joint;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = strlen_null(s1);
	len2 = strlen_null(s2);
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
   Append `to_append` to string pointed by `p_str`.
   Return FAILURE upon allocation error.
*/
int	str_append(char **p_str, char *to_append)
{
	char	*joint_str;

	joint_str = str_join_free(*p_str, to_append);
	if (joint_str == NULL)
		return (FAILURE);
	*p_str = joint_str;
	return (SUCCESS);
}

/*
   Append `char_to_append` to string pointed by `p_str`.
   Return FAILURE upon allocation error.
*/
int	str_appendc(char **p_str, char char_to_append)
{
	char	*joint_str;
	char	append[2];

	append[0] = char_to_append;
	append[1] = '\0';
	joint_str = str_join_free(*p_str, append);
	if (joint_str == NULL)
		return (FAILURE);
	*p_str = joint_str;
	return (SUCCESS);
}

/*
   Append `to_append_and_free` to string pointed by `p_str`.
   Return FAILURE upon allocation error.
*/
int	str_append_free(char **p_str, char *to_append_and_free)
{
	char	*joint_str;

	joint_str = str_join_free(*p_str, to_append_and_free);
	if (joint_str == NULL)
	{
		free(to_append_and_free);
		return (FAILURE);
	}
	*p_str = joint_str;
	free(to_append_and_free);
	return (SUCCESS);
}
