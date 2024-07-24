/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:55:54 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/22 22:49:07 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Returns 0 if `s` is NULL. */
int	strlen_null(const char *s)
{
	if (s == NULL)
		return (0);
	return ((int)ft_strlen(s));
}

/*
	Return a substring of `s` from `start_idx` to `end_idx` INCLUSIVE.
	Uses allocation so return string must be freed by the caller.
	Returns NULL upon allocation error.
*/
char	*str_sub(char *s, int start_idx, int end_idx)
{
	char	*sub;

	sub = ft_substr(s, start_idx, end_idx - start_idx + 1);
	if (sub == NULL)
		return (NULL);
	return (sub);
}

/* Return whether string only consists of digits or not. */
int	str_is_numeric(char *str)
{
	size_t	i;
	size_t	len;

	if (str == NULL)
		return (FALSE);
	len = ft_strlen(str);
	if (len == 0)
		return (FALSE);
	i = 0;
	if (str[i] == '-')
	{
		if (len == 1)
			return (FALSE);
		i ++;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/*
	Search `search_char` in `s` starting from index `search_start_idx`.
	Return -1 if not found
*/
int	str_findc_idx(char *s, int search_start_idx, char search_char)
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

/*
	Replace string pointed by `p_str` 
	from `start` index to `end` index inclusive with `replace_with`.
	Returns FAILURE upon allocation error
*/
int	str_replace_section(char **p_str, int start, int end, char *replace_with)
{
	char	*new;
	char	*new_beginning;
	char	*new_ending;

	new = NULL;
	new_beginning = str_sub(*p_str, 0, start - 1);
	if (new_beginning == NULL)
		return (FAILURE);
	if (str_append_free(&new, new_beginning) == FAILURE)
		return (FAILURE);
	if (str_append(&new, replace_with) == FAILURE)
		return (FAILURE);
	new_ending = str_sub(*p_str, end + 1, ft_strlen(*p_str) - 1);
	if (new_ending == NULL)
		return (FAILURE);
	if (str_append_free(&new, new_ending) == FAILURE)
		return (FAILURE);
	free(*p_str);
	*p_str = new;
	return (SUCCESS);
}
