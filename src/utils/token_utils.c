/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:49:08 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/19 15:04:19 by JFikents         ###   ########.fr       */
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
	if (token->value != NULL)
		new_token->value = ft_strdup(token->value);
	if (new_token->value == NULL && token->value != NULL)
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
static int	check_token_type_val(t_token_type type, char *val)
{
	if (type == REDIR_TO && !ft_strncmp(val, ">", 1))
	{
		return (FALSE);
	}
	else if (type == APPEND_TO && !ft_strncmp(val, ">>", 2))
	{
		return (FALSE);
	}
	else if (type == REDIR_FROM && !ft_strncmp(val, "<", 1))
	{
		return (FALSE);
	}
	else if (type == HERE_DOC && !ft_strncmp(val, "<<", 2))
	{
		return (FALSE);
	}
	else if (type == PIPE && !ft_strncmp(val, "|", 1))
	{
		return (FALSE);
	}
	return (TRUE);
}

void	add_token(t_token **head_ptr, t_token_type type, char *val)
{
	t_token	*last;
	t_token	*new;

	if (!check_token_type_val(type, val))
	{
		// TODO: Handle this or check at all? exit_error? return? just log/print?
	}
	new = (t_token *) malloc(1 * sizeof(t_token));
	if (new == NULL)
		// TODO: carry and free everything here
		exit_error("minishell: Error allocating memory: malloc", EXIT_FAILURE);
	new->type = type;
	new->value = ft_strdup(val);
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

void	token_list_print(t_token *head)
{
	t_token		*iter;
	const char	*enum_names[6]
		= {"STRING", "REDIR_TO", "APPEND_TO", "REDIR_FROM", "HERE_DOC", "PIPE"};

	if (head == NULL)
	{
		ft_printf("<null node>\n");
		return ;
	}
	iter = head;
	while (iter != NULL)
	{
		ft_printf("type = %-12s, val = {%s}\n", enum_names[iter->type],
			iter->value);
		iter = iter->next;
	}
	ft_printf("\n");
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
