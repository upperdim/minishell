/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:00:43 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/10 15:15:08 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
extern char	**environ;
TODO; 
?	we need ft_lexer here again so that the recently expanded env var get
?		splited again into tokens, and then insert them into the link list.
*/
void	ft_expand_env_var(t_token *token)
{
	(void) token;
	return ;
}

int	ft_move_to_next(char *input, t_token **new)
{
	int	index;

	index = 0;
	while (input[index] == ' ')
		index++;
	if (index == 0)
		return (0);
	if (input[index] == '\0')
		return (index);
	(*new)->next = ft_calloc(1, sizeof(t_token));
	if (!(*new)->next)
		return (ft_free_link_list((*new)), -1);
	(*new)->next->prev = (*new);
	(*new) = (*new)->next;
	return (index);
}

/*
void	ft_look_for_tokens_in_strs(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == SINGLE_QUOTES || tmp->type == DOUBLE_QUOTES)
		{
			tmp = tmp->next;
			continue ;
		}
		if (ft_strchr(tmp->value, '|'))
			tmp = ft_tokenize_pipe(tmp);
		// if (ft_strchr(tmp->value, '<'))
		// 	ft_tokenize_redir_from_and_here_doc(tmp);
		// if (ft_strchr(tmp->value, '>'))
		// 	ft_tokenize_redir_to_and_append_to(tmp);
		if (tmp)
			tmp = tmp->next;
	}
}
*/
