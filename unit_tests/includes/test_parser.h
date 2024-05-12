/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:25:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/12 15:28:44 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PARSER_H
# define TEST_PARSER_H

# include "parser.h"
# include "libft.h"
# include <stdlib.h>

enum e_error_type
{
	NO_ERROR,
	NO_RESULT,
	WRONG_CMD,
	NO_ARGS,
	WRONG_ARGS,
	WRONG_AND_INDEX,
	WRONG_NEXT,
	WRONG_PIPE_IN,
	WRONG_PIPE_OUT,
	WRONG_REDIR
};

#endif /* test_parser.h */