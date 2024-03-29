/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/29 13:15:58 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

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

void	parse_line(char *line);

#endif