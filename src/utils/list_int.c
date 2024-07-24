/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:30:55 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/24 16:30:23 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get a pointer to the last element of the list */
static t_list_int	*list_get_last(t_list_int *list)
{
	t_list_int	*iter;

	if (list == NULL)
		return (NULL);
	iter = list;
	while (iter->next != NULL)
		iter = iter->next;
	return (iter);
}

int	list_add(t_list_int **head_ptr, int val)
{
	t_list_int	*last;
	t_list_int	*new;

	new = (t_list_int *) malloc(1 * sizeof(t_list_int));
	if (new == NULL)
		return (FAILURE);
	new->val = val;
	new->next = NULL;
	if (*head_ptr == NULL)
	{
		*head_ptr = new;
		new->prev = NULL;
	}
	else
	{
		last = list_get_last(*head_ptr);
		last->next = new;
		new->prev = last;
	}
	return (SUCCESS);
}

/* Return number of elements the list has. */
int	list_get_size(t_list_int *head)
{
	t_list_int	*iter;
	int			size;

	size = 0;
	iter = head;
	while (iter != NULL)
	{
		++size;
		iter = iter->next;
	}
	return (size);
}

/*
	Return the integer value at the `idx` index of the list.
	Returns 0 if `idx` is not found.
	
	Caller must check if `idx` is in the range of list by using
	`list_get_size()` utility before using this.
*/
int	list_get_idx(t_list_int *head, int idx)
{
	t_list_int	*iter;
	int			i;

	i = 0;
	iter = head;
	while (iter != NULL)
	{
		if (i == idx)
			return (iter->val);
		++i;
		iter = iter->next;
	}
	return (0);
}

void	list_int_free_all(t_list_int *head)
{
	t_list_int	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free_n_null((void **)&tmp);
	}
}
