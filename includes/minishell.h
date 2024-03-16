/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:43:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/16 15:32:29 by JFikents         ###   ########.fr       */
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

typedef struct s_mallocated
{
	char				index;
	void				*ptr;
	struct s_mallocated	*next;
}	t_mallocated;

enum	e_mallocated
{
	LINE,
	PROMPT,
	DIRECTORY,
};

enum	e_check
{
	IF_NULL = -5012002,
	STATUS = 0,
	WHERE,
	INSTRUCTION,
};

// ** ---------------------------- FUNCTIONS ---------------------------- ** //
int		main(void);
char	*parse_line(char *line, t_mallocated *mallocated);
void	errors(int check[3], void *if_null, t_mallocated *mallocated);

#endif
