/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tunsal <tunsal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:43:00 by tunsal            #+#    #+#             */
/*   Updated: 2024/07/17 15:14:28 by tunsal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "exec.h"
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
# include <errno.h>
# include <limits.h>

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

# define TRUE 1
# define FALSE 0

void	ft_execve(t_cmd *cmd);
char	*get_prompt(void);
void	set_signal_handlers(void);
char	**dup_environ(void);

/* ****************************************************************************/
/*                                   UTILS                                    */
/* ****************************************************************************/
// String
int		strlen_null(const char *s);
char	*str_sub(char *s, int start_idx, int end_idx);
int		str_is_numeric(char *str);
int		find_idx_of_nextc(char *s, int search_start_idx, char search_char);
void	str_replace_section(char **p_str, int start, int end, char *replace_with);

// String append
void	str_append(char **p_str, char *to_append);
void	str_appendc(char **p_str, char char_to_append);
void	str_append_free(char **p_str, char *to_append_and_free);

// Int list
void	list_add(t_list_int **head_ptr, int val);
void	list_print(t_list_int *head);
int		list_get_size(t_list_int *head);
long	list_get_val_idx(t_list_int *head, int idx);

// Token list
void	add_token(t_token **head_ptr, t_token_type type, char *val);
void	token_list_print(t_token *head);
t_token	*token_list_get_last(t_token *list);

// Error management
void	exit_perror(int exit_status);
void	exit_error(char *error_msg, int exit_status);
void	clean_up(void);

// Misc
long	ft_atol(const char *str);

/* ****************************************************************************/
/*                                 EXECUTION                                  */
/* ****************************************************************************/
// TODO: If these are execution, why aren't they in exec.h?
char	*find_path_to(char *cmd);
int		setup_in_pipe(int p_fd[2]);
int		setup_out_pipe(int p_fd[2]);

/* ****************************************************************************/
/*                                 BUILTINS                                   */
/* ****************************************************************************/
int		exec_builtins(t_cmd *cmd);
int		echo(char **input);
int		env(const int argc);
int		exit_bash(const int argc, t_cmd *cmd);
int		pwd(void);
int		cd(const int argc, char **argv);
int		export(const int argc, char **argv);
int		add_env_var(char *var);
int		unset_builtin(char **argv);
bool	have_same_key(const char *key, char *env_var);

#endif
