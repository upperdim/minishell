/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 15:00:22 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/02 18:47:08 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*make_env_bigger(char *var)
{
	extern char	**environ;
	char		**new_environ;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	new_environ = ft_calloc(sizeof(char *), (i + 2));
	if (new_environ == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), NULL);
	i = -1;
	while (environ[++i])
		new_environ[i] = environ[i];
	new_environ[i] = ft_strdup(var);
	if (new_environ[i] == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "env", E_ALLOC), NULL);
	new_environ[i + 1] = NULL;
	free_2d_array((void **)environ, FREE_ANY_SIZE);
	environ = new_environ;
	return (environ[i]);
}

void	*add_env_var(char *var)
{
	const char	*value = ft_strchr(var, '=');
	char		*key;
	int			i;
	extern char	**environ;

	if (value == NULL)
		return (NULL);
	key = ft_substr(var, 0, value - var);
	if (key == NULL)
		return (ft_putstr_fd(E_ALLOC, 2), NULL);
	if (getenv(key) == NULL)
		return (free(key), make_env_bigger(var));
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
	return (free(key), environ[i]);
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
