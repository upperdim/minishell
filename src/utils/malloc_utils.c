/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:02:07 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/22 15:59:37 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_alloc_list	*last_in_list(t_alloc_list *mallocated)
{
	t_alloc_list	*tmp;

	tmp = mallocated;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	free_all_list(t_alloc_list *to_free)
{
	t_alloc_list	*tmp;

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
		if (to_free->index != -1 && !to_free->next)
			ft_free_n_null((void **)&to_free);
		to_free = tmp;
	}
}

void	add_to_list(void *ptr, int index, t_alloc_list *to_free)
{
	t_alloc_list	*new;
	t_alloc_list	*last;

	if (to_free->index == -1)
	{
		to_free->index = index;
		to_free->ptr = ptr;
		return ;
	}
	new = ft_calloc(sizeof(t_alloc_list), 1);
	if (!new)
		clean_exit(to_free);
	new->index = index;
	new->ptr = ptr;
	new->next = NULL;
	last = last_in_list(to_free);
	last->next = new;
}

void	free_from_list(t_alloc_list *to_free, int index)
{
	t_alloc_list	*tmp;

	tmp = to_free;
	while (tmp->index != index && tmp->next)
		tmp = tmp->next;
	if (tmp->index != index)
		return ;
	if (!tmp->next || tmp == to_free)
	{
		tmp->index = -1;
		ft_free_n_null(&(tmp->ptr));
		return ;
	}
	while (to_free->next != tmp && to_free != tmp)
		to_free = to_free->next;
	if (to_free->next && to_free->next == tmp)
		to_free->next = tmp->next;
	ft_free_n_null(&tmp->ptr);
	ft_free_n_null((void **)&tmp);
}
