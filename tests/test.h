/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/24 20:45:07 by JFikents         ###   ########.fr       */
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

void	test_builtins(void);

#endif