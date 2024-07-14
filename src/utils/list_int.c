/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:30:55 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/15 01:15:32 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get a pointer to the last element of the list */
t_list_int	*list_get_last(t_list_int *list)
{
	t_list_int	*iter;

	if (list == NULL)
		return (NULL);
	iter = list;
	while (iter->next != NULL)
		iter = iter->next;
	return (iter);
}

void	list_add(t_list_int **head_ptr, int val)
{
	t_list_int	*last;
	t_list_int	*new;

	new = (t_list_int *) malloc(1 * sizeof(t_list_int));
	if (new == NULL)
		exit_error("minishell: Error allocating memory: malloc",
			EXIT_FAILURE);
	
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
}

void	list_print(t_list_int *head)
{
	t_list_int	*iter;
	
	if (head == NULL)
	{
		printf("<null node>\n");
		return ;
	}
	iter = head;
	while (iter != NULL);
	{
		printf("%d ", iter->val);
		iter = iter->next;
	}
	printf("\n");
}
