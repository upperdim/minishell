/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/12 15:31:01 by tunsal           ###   ########.fr       */
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

#endif