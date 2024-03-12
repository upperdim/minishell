/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:43:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/12 15:39:25 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

/**
	@note//_DESCRIPTION
	@brief #### Check file access permissions.
	@brief Checks whether the calling process can access the file in the path
		`pathname` with the permissions specified by `mode`.
	@note//_PARAMETERS
	@param pathname The path to the file to be checked.
	@param mode The permissions to be checked. The permissions can be combined
		using the bitwise OR operator.
	@note//_RETURNS
	@return 0 if the file can be accessed with the permissions specified by
		`mode`, or -1 if an error occurred.
	@note//_NOTES
	@note available permissions are: R_OK, W_OK, X_OK, F_OK. Read, Write, Execute
		and File exists respectively.
 */
int		access(const char *pathname, int mode);

/**
	@note//_DESCRIPTION
	@brief #### Wait for a child process to terminate.
	@brief The function suspends the execution of the calling process until one
		of its child processes terminates.
	@note//_PARAMETERS
	@param status Tells under which conditions the function should return.
	@note//_RETURNS
	@return The process ID of the terminated child process, or -1 if an error
		occurred.
	@note//_NOTES
	@note
	@note//_WARNINGS
	@warning
 */
pid_t	wait(int *status);



#endif