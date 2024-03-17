/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:02:07 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 20:34:25 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_mallocated	*last_mallocated(t_mallocated *mallocated)
{
	t_mallocated	*tmp;

	tmp = mallocated;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	full_free(t_mallocated *to_free)
{
	t_mallocated	*tmp;

	while (to_free)
	{
		if (!to_free->next)
		{
			to_free->index = -1;
			ft_free_n_null(&(to_free->ptr));
			return ;
		}
		tmp = to_free->next;
		ft_free_n_null(&to_free->ptr);
		ft_free_n_null((void **)&to_free);
		to_free = tmp;
	}
}

void	needs_free(void *ptr, int index, t_mallocated *to_free)
{
	t_mallocated	*new;
	t_mallocated	*last;

	if (to_free->index == -1)
	{
		to_free->index = index;
		to_free->ptr = ptr;
		return ;
	}
	new = ft_calloc(sizeof(t_mallocated), 1);
	check((int [3]){IF_NULL, 0, 0}, new, to_free);
	new->index = index;
	new->ptr = ptr;
	new->next = NULL;
	last = last_mallocated(to_free);
	last->next = new;
}

void	rm_from_to_free(t_mallocated *to_free, int index)
{
	t_mallocated	*tmp;

	tmp = to_free;
	while (tmp->index != index && tmp->next)
		tmp = tmp->next;
	if (tmp->index != index)
		return ;
	if (!tmp->next)
	{
		tmp->index = -1;
		ft_free_n_null(&(tmp->ptr));
		return ;
	}
	while (to_free->next != tmp)
		to_free = to_free->next;
	to_free->next = tmp->next;
	ft_free_n_null(&tmp->ptr);
	ft_free_n_null((void **)&tmp);
}
