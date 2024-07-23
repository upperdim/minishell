/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:49:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/23 02:15:30 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Isolates a token from the linked list.
 * 
 * @param token the token to isolate
 * @return t_token* the next token after the isolated token or if there is no
 * 	next token, the previous token, or NULL if there is no previous token either.
 */
t_token	*isolate_token(t_token **token)
{
	t_token	*isolated_token;

	isolated_token = *token;
	*token = (*token)->next;
	if (isolated_token->prev)
		isolated_token->prev->next = isolated_token->next;
	isolated_token->prev = NULL;
	if (isolated_token->next)
		isolated_token->next->prev = isolated_token->prev;
	isolated_token->next = NULL;
	return (isolated_token);
}

t_token	*dup_token(t_token *token)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (new_token == NULL)
	{
		ft_free_link_list(token);
		exit_error("minishell: "E_ALLOC, 1);
	}
	new_token->value = ft_strdup(token->value);
	if (new_token->value == NULL)
	{
		ft_free_n_null((void **)&new_token);
		ft_free_link_list(token);
		exit_error("minishell: "E_ALLOC, 1);
	}
	new_token->type = token->type;
	return (new_token);
}

void	add_token_last(t_token **head, t_token **new)
{
	t_token	*last;
	t_token	*new_token;

	new_token = dup_token(*new);
	if (*head == NULL)
	{
		*head = new_token;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_token;
	new_token->prev = last;
}

/* Get a pointer to the last element of the token list */
t_token	*token_list_get_last(t_token *list)
{
	t_token	*iter;

	if (list == NULL)
		return (NULL);
	iter = list;
	while (iter->next != NULL)
		iter = iter->next;
	return (iter);
}

/* Return whether token type and value are compatible */
// static int	check_token_type_val(t_token_type type, char *val)
// {
// 	if (type == REDIR_TO && !ft_strncmp(val, ">", 1))
// 	{
// 		return (FALSE);
// 	}
// 	else if (type == APPEND_TO && !ft_strncmp(val, ">>", 2))
// 	{
// 		return (FALSE);
// 	}
// 	else if (type == REDIR_FROM && !ft_strncmp(val, "<", 1))
// 	{
// 		return (FALSE);
// 	}
// 	else if (type == HERE_DOC && !ft_strncmp(val, "<<", 2))
// 	{
// 		return (FALSE);
// 	}
// 	else if (type == PIPE && !ft_strncmp(val, "|", 1))
// 	{
// 		return (FALSE);
// 	}
// 	return (TRUE);
// }

static void	add_token_handle_failure(\
t_token **head_ptr, t_exp_idxs *free_on_err, char *line)
{
	ft_free_link_list(*head_ptr);
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
	ft_free_link_list(*head_ptr);
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

void	ft_free_link_list(t_token *split)
{
	t_token	*tmp;

	while (split)
	{
		tmp = split;
		split = split->next;
		ft_free_n_null((void **)&tmp->value);
		ft_free_n_null((void **)&tmp);
	}
}
