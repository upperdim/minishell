/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 10:29:54 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

# define NOT_QUOTE 0

typedef enum e_token_type
{
	STRING,
	REDIR_TO,
	APPEND_TO,
	REDIR_FROM,
	HERE_DOC,
	PIPE,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_list_int
{
	int					val;
	struct s_list_int	*next;
	struct s_list_int	*prev;
}	t_list_int;


/* Parser variables */
typedef struct s_pvars
{
	char	*line;
	int		len;
	t_token	*head;
}	t_pvars;

void	detect_tilda_expansions(char *line, t_list_int **p_tild_idxs_to_expand);
void	detect_var_expansions(char *line, t_list_int **p_var_idxs_to_ex, int s);
t_token	*tokenize(char *line);

#endif