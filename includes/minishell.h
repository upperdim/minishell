/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:43:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/27 12:16:05 by JFikents         ###   ########.fr       */
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
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>

# ifdef COLOR

#  ifndef CYAN
#   define CYAN "\x1b[38;5;14m"
#  endif
#  ifndef BLUE
#   define BLUE "\x1b[38;5;32m"
#  endif
#  ifndef WHITE
#   define WHITE "\x1b[0m"
#  endif

# else

#  ifndef CYAN
#   define CYAN ""
#  endif
#  ifndef BLUE
#   define BLUE ""
#  endif
#  ifndef WHITE
#   define WHITE ""
#  endif

# endif 

/* ft_free_2d_arrays frees arrays of any size with this argument */
# define FREE_ANY_SIZE -1

typedef struct s_alloc_list
{
	int					index;
	void				*ptr;
	struct s_alloc_list	*next;
}	t_alloc_list;

enum	e_list_index
{
	INPUT,
	HOSTNAME
};

enum	e_pipes
{
	PIPE_FD_READ,
	PIPE_FD_WRITE
};

// ** ---------------------------- FUNCTIONS ---------------------------- ** //

void	ft_execve(char **argv, char **envp, int pipe_fd[2]);
char	*get_prompt(void);
void	set_signal_handlers(void);
void	free_from_list(t_alloc_list *to_free, int index);
void	free_all_list(t_alloc_list *to_free);
void	add_to_list(void *ptr, int index, t_alloc_list *to_free);
void	parse_line(char *line);
void	clean_exit(t_alloc_list *mallocated);
// EXEC
char	*check_for_cmd(char *cmd);
int		setup_in_pipe(int p_fd[2]);
int		setup_out_pipe(int p_fd[2]);
// BUILTINS
void	builtins(char *input);
void	echo(char *input);
void	env(char *input);
void	exit_bash(char **input);
void	pwd(void);
void	cd(char *input);

#endif
