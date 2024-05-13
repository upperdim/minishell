/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:49:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/05/12 15:59:12 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "minishell.h"

# ifndef RED
#  define RED "\x1b[0;31m"
# endif

# ifndef GREEN
#  define GREEN "\x1b[0;32m"
# endif

# ifndef DEFAULT
#  define DEFAULT "\x1b[0m"
# endif
////////////////////////////		UTILITIES		////////////////////////////
void	test_1_builtins(void);
void	print_feedback(char *test, char *output, char *expected);
pid_t	start_minishell_builtins(int *pipe_write);
void	reset_tty(pid_t pid);
char	*get_test_input(int fd);

////////////////////////////		  ECHO  		////////////////////////////
void	echo_test_1(int read_output_fd);
void	echo_test_2(int read_output_fd);
void	echo_test_3(int read_output_fd);
void	echo_test_4(int read_output_fd);
void	echo_test_5(int read_output_fd);
void	echo_test_6(int read_output_fd);

////////////////////////////		  EXIT  		////////////////////////////
void	exit_test_1(int read_output_fd, int status);

////////////////////////////		   CD   		////////////////////////////
void	cd_test_1(int read_output_fd);

#endif