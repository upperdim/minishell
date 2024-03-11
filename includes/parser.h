/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:11:30 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/11 19:28:12 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// ** ------------------------- MACROS AND ENUMS ------------------------- ** //

/* Command, a program */
# define TOKEN_CMD 101
/* Argument of a command/program */
# define TOKEN_ARG 102

# define TOKEN_PIPE 107

/* Redirection overwrite left (<) */
# define TOKEN_REDIR_OVER_L 103
/* Redirection overwrite right (>) */
# define TOKEN_REDIR_OVER_R 104
/* Redirection append left (<<) */
# define TOKEN_REDIR_APPD_L 105
/* Redirection append right (>>) */
# define TOKEN_REDIR_APPD_R 106

/* Single quote (') */
# define TOKEN_QUOTE_S 108
/* Double quote ("') */
# define TOKEN_QUOTE_D 109

//_--------------------------------------------------------------------------_//

#endif