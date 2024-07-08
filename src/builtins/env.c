/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/08 17:36:46 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*make_env_bigger(char *var)
{
	extern char	**environ;
	const int	environ_size = count_strs_in_array(environ);
	char		**new_environ;
	int			i;

	new_environ = ft_calloc(sizeof(char *), (environ_size + 2));
	if (new_environ == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), NULL);
	i = -1;
	while (environ[++i])
		new_environ[i] = environ[i];
	new_environ[i] = ft_strdup(var);
	if (new_environ[i] == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), NULL);
	ft_free_2d_array((void ***)&environ, FREE_ANY_SIZE);
	environ = new_environ;
	return (environ[i]);
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

void	*add_env_var(char *var)
{
	const char	*key = get_key(var);
	extern char	**environ;
	int			i;

	if (key == NULL)
		return (NULL);
	if (getenv(key) == NULL)
		return (ft_free_n_null((void **)&key), make_env_bigger(var));
	i = -1;
	while (environ[++i])
	{
		if (ft_strncmp(environ[i], key, ft_strlen(key)) == 0)
		{
			ft_free_n_null((void **)&environ[i]);
			environ[i] = ft_strdup(var);
			if (environ[i] == NULL)
			{
				ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC);
				return (ft_free_n_null((void **)&key), NULL);
			}
			break ;
		}
	}
	return (ft_free_n_null((void **)&key), environ[i]);
}

void	env(const int argc)
{
	extern char	**environ;
	int			i;

	if (argc > 1)
	{
		ft_printf_fd(2, ERROR_MSG, "env", "Too many arguments");
		return ;
	}
	i = -1;
	while (environ[++i])
		if (ft_strchr(environ[i], '=') != NULL)
			ft_putendl_fd(environ[i], 1);
}
