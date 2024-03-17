/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:43:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/17 20:32:56 by JFikents         ###   ########.fr       */
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

# ifndef CYAN
#  define CYAN "\x1b[38;5;14m"
# endif

# ifndef BLUE
#  define BLUE "\x1b[38;5;32m"
# endif

# ifndef WHITE
#  define WHITE "\x1b[0m"
# endif

typedef struct s_mallocated
{
	char				index;
	void				*ptr;
	struct s_mallocated	*next;
}	t_mallocated;

enum	e_mindex
{
	INPUT,
};

enum	e_check
{
	IF_NULL = -5012002,
	EXIT = -20020105,
	STATUS = 0,
	WHERE,
	INSTRUCTION,
};

// ** ---------------------------- FUNCTIONS ---------------------------- ** //
void	env(char *input);
void	exit_bash(char *input, t_mallocated *to_free);
void	echo(char *input);
void	builtins(char *input, t_mallocated *to_free);
char	*prompt(t_mallocated *to_free);
void	set_signal_handlers(void);
void	rm_from_to_free(t_mallocated *to_free, int index);
void	full_free(t_mallocated *to_free);
void	needs_free(void *ptr, int index, t_mallocated *to_free);
void	pwd(char *input, t_mallocated *to_free);
void	cd(char *input, t_mallocated *to_free);
int		main(void);
char	*parse_line(char *line, t_mallocated *mallocated);
void	check(int check[3], void *if_null, t_mallocated *mallocated);

#endif
