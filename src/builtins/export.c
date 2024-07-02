/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:18:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/02 15:46:40 by JFikents         ###   ########.fr       */
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
		return (ft_putstr_fd(E_ALLOC, 2), NULL);
	i = -1;
	while (environ[++i])
		new_environ[i] = environ[i];
	new_environ[i] = ft_strdup(var);
	if (new_environ[i] == NULL)
		return (ft_putstr_fd(E_ALLOC, 2), NULL);
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

	value = ft_strchr(var, '=');
	if (value == NULL)
		return (ft_putstr_fd("minishell: export: invalid argument", 2), NULL);
	key = ft_substr(var, 0, value - var);
	if (key == NULL)
		return (ft_putstr_fd(E_ALLOC, 2), NULL);
	tmp = ft_strjoin(key, "=");
	if (tmp == NULL)
		return (ft_putstr_fd(E_ALLOC, 2), NULL);
	if (ft_getenv(key) == NULL)
		ft_addenv(tmp);
	else
		ft_setenv(tmp);
	ft_free_n_null((void **)&key);
	ft_free_n_null((void **)&tmp);
	return (NULL);
}
