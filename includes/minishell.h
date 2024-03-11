/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:43:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/11 21:14:58 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ** ---------------------------- LIBRARIES ---------------------------- ** //

# include "parser.h"
# include "libft.h"
# include <stdio.h>//printf
# include <stdlib.h>//malloc
# include <unistd.h>//write
# include <fcntl.h>//open
# include <sys/wait.h>//waitpid

//_--------------------------------------------------------------------------_//

//? * ------------------------ ALLOWED FUNCTIONS ------------------------ * ?//

/*									NOTE
!	The following functions are from the libraries included, the doocumentation
! here is only for reference. For exact information about the functions, see the
! library's documentation.
*/

/**
	@note//_DESCRIPTION
	@brief #### Print formatted data to stdout.
	@brief The function writes output with the apropiate format given by the
		the string `format`, to the standard output stream.
	@note//_PARAMETERS
	@param format The string that contains the text to be written including the
		instructions to format the variables if used with variables.
	@param ... The variables to be printed in the format given by `format`.
	@note//_RETURNS
	@return The number of characters printed, or a negative number if an error
		occurred.
 */
int		printf(const char *format, ...);

/**
	@note//_DESCRIPTION
	@brief #### Allocate memory block. (USE 'ft_calloc' INSTEAD)
	@brief The function allocates a block of memory of `size` bytes, and returns
		a pointer to the beginning of the block.
	@note//_PARAMETERS
	@param size The size of the memory block to be allocated.
	@note//_RETURNS
	@return A pointer to the beginning of the block of memory allocated, or NULL
		if the function failed to allocate the memory.
	@note//_NOTES
	@note Always check the return value to make sure the memory was allocated.
	@note//_WARNINGS
	@warning The memory allocated by `malloc` is not initialized, and may
		contain garbage values.
	@warning The memory allocated by `malloc` must be freed with `free` when it
		is no longer needed.
 */
void	*malloc(size_t size);

/**
	@note//_DESCRIPTION
	@brief #### Deallocate memory block. (TRY USING 'ft_free_n_null' or 
	`ft_free_2d_array` INSTEAD)
	@brief The function deallocates the memory block pointed by `ptr`, which
		must have been returned by a previous call to `malloc`, `calloc` or
		`realloc`.
	@note//_PARAMETERS
	@param ptr A pointer to a memory block previously allocated by `malloc`,
		`calloc` or `realloc`.
	@note//_NOTES
	@note for best practices, always set the pointer to NULL after freeing it.
	@note You can use the function `ft_free_n_null` or `ft_free_2d_array` to
		free the memory and set the pointer to NULL in one step.
	@note//_WARNINGS
	@warning The behavior is undefined if the value of `ptr` is not a pointer to a
		memory block previously allocated by `malloc`, `calloc` or `realloc`.
 */
void	free(void *ptr);

/**
	@note//_DESCRIPTION
	@brief #### Write to a file descriptor.
	@brief The function writes `count` bytes from the buffer pointed by `buf` to
		the file referred to by the file descriptor `fd`.
	@note//_PARAMETERS
	@param fd the file descriptor to write to.
	@param buf the buffer containing the data to be written.
	@param count the number of bytes to write.
	@note//_RETURNS
	@return The number of bytes written, or -1 if an error
		occurred.
	@note//_NOTES
	@note The file descriptor `fd` must be open for writing.
	@note The function may write fewer bytes than requested if the buffer is
		smaller than `count`.
	@note//_WARNINGS
	@warning if the file descriptor `fd` is not open for writing, the behavior
		is undefined.
 */
ssize_t	write(int fd, const void *buf, size_t count);

/**
	@note//_DESCRIPTION
	@brief #### Open a file.
	@brief The function opens the file in the path `pathname` with the flags
		specified by `flags`, and returns a file descriptor that can be used to
		perform I/O operations on the file.
	@note//_PARAMETERS
	@param pathname The path to the file to be opened.
	@param flags The flags to be used when opening the file. The flags can be
		combined using the bitwise OR operator.
	@param ... the flags needed if flags include O_CREAT.
	@note//_RETURNS
	@return The file descriptor of the file opened, or -1 if an error occurred.
 */
int		open(const char *pathname, int flags, ...);

/*
	access
	read
	close
	fork
	wait
char	*readline(void);
	rl_clear_history
	rl_on_new_line
	rl_replace_line
	rl_redisplay
	add_history
	waitpid
	wait3
	wait4
	signal
	sigaction
	sigemptyset
	sigaddset
	kill
	exit
	getcwd
	chdir
	stat
	lstat
	fstat
	unlink
	execve
	dup
	dup2
	pipe
	opendir
	readdir
	closedir
	strerror
	perror
	isatty
	ttyname
	ttyslot
	ioctl
	getenv
	tcsetattr
	tcgetattr
	tgetent
	tgetflag
	tgetnum
	tgetstr
	tgoto
	tputs
	*/

//_--------------------------------------------------------------------------_//

#endif