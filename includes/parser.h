/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/05/10 19:51:45 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

enum	e_token
{
	CMD,
	ARG,
	PIPE,
	REDIR_OVER_L,
	REDIR_OVER_R,
	REDIR_APPD_L,
	REDIR_APPD_R,
	QUOTE_S,
	QUOTE_D
};

typedef struct s_split
{
	char			*result;
	struct s_split	*next;
}	t_split;

typedef struct s_flags
{
	int		pipe_in;
	int		pipe_out;
	int		redir;
}	t_flags;

typedef struct s_instruction
{
	char					*cmd;
	char					**args;
	int						and_index;
	struct s_instruction	*next;
	t_flags					flags;
}	t_instruction;

t_instruction	*parse_line(char *line);
t_split			*ft_split_strings(char *input);

#endif