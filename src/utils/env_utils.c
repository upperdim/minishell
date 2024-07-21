/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:16:47 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/21 19:00:37 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_environ(void)
{
	extern char	**environ;
	int			env_var_count;
	char		**new_env;

	env_var_count = count_strs_in_array(environ);
	new_env = ft_calloc(env_var_count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	env_var_count = 0;
	while (environ[env_var_count])
	{
		new_env[env_var_count] = ft_strdup(environ[env_var_count]);
		if (!new_env[env_var_count])
			return (ft_free_2d_array((void ***)&new_env, FREE_ANY_SIZE), NULL);
		env_var_count++;
	}
	return (new_env);
}

static int	make_env_bigger(char *var)
{
	extern char	**environ;
	const int	environ_size = count_strs_in_array(environ);
	char		**new_environ;
	int			i;

	new_environ = ft_calloc(sizeof(char *), (environ_size + 2));
	if (new_environ == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), EXIT_FAILURE);
	i = -1;
	while (environ[++i])
		new_environ[i] = environ[i];
	new_environ[i] = ft_strdup(var);
	if (new_environ[i] == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC),
			ft_free_2d_array((void ***)&new_environ, -1), EXIT_FAILURE);
	ft_free_n_null((void **)&environ);
	environ = new_environ;
	return (EXIT_SUCCESS);
}

static const char	*get_key(char *var)
{
	const char	*value = ft_strchr(var, '=');
	const char	*key;
	int			key_len;

	key_len = ft_strlen(var);
	if (value != NULL)
		key_len = value - var;
	key = ft_substr(var, 0, key_len);
	if (key == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), NULL);
	return (key);
}

int	add_env_var(char *var)
{
	const char	*key = get_key(var);
	extern char	**environ;
	int			i;

	if (key == NULL)
		return (EXIT_FAILURE);
	i = -1;
	while (environ[++i] && ft_strchr(var, '=') != NULL)
	{
		if (have_same_key(key, environ[i]) == true)
		{
			ft_free_n_null((void **)&environ[i]);
			environ[i] = ft_strdup(var);
			if (environ[i] == NULL)
			{
				ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC);
				return (ft_free_n_null((void **)&key), EXIT_FAILURE);
			}
			break ;
		}
	}
	if (getenv(key) == NULL
		&& (environ[i] == NULL || ft_strchr(var, '=') == NULL))
		return (ft_free_n_null((void **)&key), make_env_bigger(var));
	return (ft_free_n_null((void **)&key), EXIT_SUCCESS);
}

int	set_last_process_exit_code(int exit_status)
{
	char	*exit_code;
	char	*var_exit_code;

	exit_code = ft_itoa(exit_status);
	if (exit_code == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), EXIT_FAILURE);
	var_exit_code = ft_strjoin("LAST_PROCESS_EXIT_CODE=", exit_code);
	ft_free_n_null((void **)&exit_code);
	if (var_exit_code == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), EXIT_FAILURE);
	if (add_env_var(var_exit_code) == EXIT_FAILURE)
		return (ft_free_n_null((void **)&var_exit_code), EXIT_FAILURE);
	ft_free_n_null((void **)&var_exit_code);
	return (EXIT_SUCCESS);
}
