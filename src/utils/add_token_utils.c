/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:31:02 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/24 16:32:04 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token_handle_failure(\
t_token **head_ptr, t_exp_idxs *free_on_err, char *line)
{
	free_tokens(*head_ptr);
	exit_free_exp_idxs(ERR_MSG_MALLOC, free_on_err, line);
}

void	add_token(\
t_token **head_ptr, t_token_type type, char *val, t_tokenizer_vars *v)
{
	t_token	*last;
	t_token	*new;

	new = (t_token *) malloc(1 * sizeof(t_token));
	if (new == NULL)
		add_token_handle_failure(head_ptr, v->free_on_err, v->line);
	new->type = type;
	new->value = ft_strdup(val);
	if (new->value == NULL)
		add_token_handle_failure(head_ptr, v->free_on_err, v->line);
	new->next = NULL;
	if (*head_ptr == NULL)
	{
		*head_ptr = new;
		new->prev = NULL;
	}
	else
	{
		last = token_list_get_last(*head_ptr);
		last->next = new;
		new->prev = last;
	}
}

static void	add_tok_free_val_handle_failure(\
t_token **head_ptr, t_exp_idxs *free_on_err, char *line, char *val)
{
	if (val != NULL)
		free(val);
	free_tokens(*head_ptr);
	exit_free_exp_idxs(ERR_MSG_MALLOC, free_on_err, line);
}

void	add_token_free_val(\
t_token **head_ptr, t_token_type type, char *val, t_tokenizer_vars *v)
{
	t_token	*last;
	t_token	*new;

	new = (t_token *) malloc(1 * sizeof(t_token));
	if (new == NULL)
		add_tok_free_val_handle_failure(head_ptr, v->free_on_err, v->line, val);
	new->type = type;
	new->value = ft_strdup(val);
	if (new->value == NULL)
		add_tok_free_val_handle_failure(head_ptr, v->free_on_err, v->line, val);
	new->next = NULL;
	if (*head_ptr == NULL)
	{
		*head_ptr = new;
		new->prev = NULL;
	}
	else
	{
		last = token_list_get_last(*head_ptr);
		last->next = new;
		new->prev = last;
	}
	free(val);
}

int	add_token_last(t_token **head, t_token **new)
{
	t_token	*last;
	t_token	*new_token;

	new_token = dup_token(*new);
	if (new_token == NULL)
		return (EXIT_FAILURE);
	if (*head == NULL)
	{
		*head = new_token;
		return (EXIT_SUCCESS);
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_token;
	new_token->prev = last;
	return (EXIT_SUCCESS);
}
