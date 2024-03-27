/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/27 12:33:06 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"

# ifndef RED
#  define RED "\033[0;31m"
# endif

# ifndef GREEN
#  define GREEN "\033[0;32m"
# endif

# ifndef DEFAULT
#  define DEFAULT "\x1b[0m"
# endif

void	test_builtins(void);

#endif