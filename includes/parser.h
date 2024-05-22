/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/22 16:02:01 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

enum	e_token
{
	STRING,
	DOUBLE_QUOTES,
	SINGLE_QUOTES,
	REDIR_TO,
	APPEND_TO,
	REDIR_FROM,
	HERE_DOC,
	PIPE,
};

typedef struct s_token
{
	char			*content;
	enum e_token	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


t_token			*parse_line(char *line);
t_token			*ft_lexer(char *input);
void			ft_free_link_list(t_token *split);
void			ft_expand_env_var(t_token *token);
int				ft_move_to_next(char *input, t_token **new);
void			ft_look_for_tokens_in_strs(t_token *head);
t_token			*ft_tokenize_pipe(t_token *token);

#endif