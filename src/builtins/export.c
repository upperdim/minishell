/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:18:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/01 18:32:42 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*add_env_var(char *var)
{
	char	*value;
	char	*key;
	char	*tmp;

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
