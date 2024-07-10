/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:16:47 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/09 15:18:33 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_environ(void)
{
	extern char	**environ;
	int			env_var_count;
	char		**new_env;

	env_var_count = 0;
	while (environ[env_var_count])
		env_var_count++;
	new_env = ft_calloc(env_var_count + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	env_var_count = 0;
	while (environ[env_var_count])
	{
		new_env[env_var_count] = ft_strdup(environ[env_var_count]);
		if (!new_env[env_var_count])
			return (ft_free_2d_array((void ***)&new_env, -1), NULL);
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
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), EXIT_FAILURE);
	ft_free_2d_array((void ***)&environ, FREE_ANY_SIZE);
	environ = new_environ;
	return (EXIT_SUCCESS);
}

static const char	*get_key(char *var)
{
	const char	*value = ft_strchr(var, '=');
	const char	*key;

	key = ft_substr(var, 0, value - var);
	if (value == NULL)
		return (NULL);
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
	if (getenv(key) == NULL)
		return (ft_free_n_null((void **)&key), make_env_bigger(var));
	i = -1;
	while (environ[++i])
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
	return (ft_free_n_null((void **)&key), EXIT_SUCCESS);
}
