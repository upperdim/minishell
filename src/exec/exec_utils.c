/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:15:16 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/21 13:34:29 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	while ((*cmd)->prev != NULL)
		*cmd = (*cmd)->prev;
	while (*cmd != NULL)
	{
		tmp = *cmd;
		*cmd = (*cmd)->next;
		if (tmp->argv && tmp->argv != (void *)1)
			ft_free_2d_array((void ***)&tmp->argv, FREE_ANY_SIZE);
		free_tokens(tmp->strs);
		free_tokens(tmp->redirects);
		ft_close(&tmp->pipe[PIPE_FD_READ]);
		ft_close(&tmp->pipe[PIPE_FD_WRITE]);
		ft_free_n_null((void **)&tmp);
	}
}

bool	is_builtin(const char *cmd)
{
	const char	*builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset", NULL};
	const char	*lowercase_cmd = dup_in_lowercase(cmd);
	int			i;

	if (lowercase_cmd == NULL)
		return (-1);
	i = -1;
	while (builtins[++i] != NULL)
	{
		if (ft_strncmp(lowercase_cmd, builtins[i], ft_strlen(builtins[i]) + 1)
			== 0)
		{
			ft_free_n_null((void **)&lowercase_cmd);
			return (true);
		}
	}
	ft_free_n_null((void **)&lowercase_cmd);
	return (false);
}

char	**transform_to_array(t_token *token)
{
	char	**argv;
	int		argc;

	argc = 1;
	if (token == NULL)
		return ((void *)1);
	while (token->next != NULL && ++argc)
		token = token->next;
	argv = ft_calloc(argc + 1, sizeof(char *));
	if (argv == NULL)
		return (NULL);
	while (token->prev != NULL)
		token = token->prev;
	argc = 0;
	while (token != NULL)
	{
		if (token->value != NULL)
			argv[argc++] = ft_strdup(token->value);
		else
			argv[argc++] = ft_strdup("");
		token = token->next;
	}
	return (argv);
}

static char	**format_path(char *no_format_path)
{
	char	**env_path;
	char	*tmp;
	int		i;

	i = 0;
	env_path = ft_split(no_format_path, ':');
	if (!env_path)
		return (ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC), NULL);
	while (env_path[i])
	{
		tmp = ft_strjoin(env_path[i], "/");
		if (!tmp)
		{
			ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC);
			return (ft_free_2d_array((void ***)&env_path, FREE_ANY_SIZE), NULL);
		}
		ft_free_n_null((void **)&env_path[i]);
		env_path[i] = tmp;
		i++;
	}
	return (env_path);
}

char	*find_path_to(char *cmd)
{
	char	*abs_path_cmd;
	char	*test_path;
	int		i;
	char	**env_path;

	i = 0;
	abs_path_cmd = NULL;
	env_path = format_path(getenv("PATH"));
	while (env_path[i] && !abs_path_cmd)
	{
		test_path = ft_strjoin(env_path[i], cmd);
		if (!test_path)
			return (ft_printf_fd(2, ERROR_MSG, "exec", E_ALLOC), NULL);
		if (!access(test_path, X_OK))
			abs_path_cmd = test_path;
		else
			ft_free_n_null((void **)&test_path);
		i++;
	}
	ft_free_2d_array((void ***)&env_path, FREE_ANY_SIZE);
	return (abs_path_cmd);
}
