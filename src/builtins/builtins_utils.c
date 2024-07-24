/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:18:58 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/24 19:48:01 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	have_same_key(const char *key, char *env_var)
{
	const char	*equal_sign = ft_strchr(env_var, '=');
	size_t		env_key_len;

	env_key_len = ft_strlen(env_var);
	if (equal_sign != NULL)
		env_key_len = equal_sign - env_var;
	if (ft_strlen(key) != env_key_len)
		return (false);
	if (ft_strncmp(key, env_var, env_key_len) == 0)
		return (true);
	return (false);
}

int	is_key_valid(char *key)
{
	int	i;

	if (key == NULL || ft_isdigit(key[0] || ft_isalnum(key[0]) == false)
		|| key[0] == '=' || key[0] == '+')
		return (false);
	i = -1;
	while (key[++i] != '\0' && key[i] != '=' && key[i] != '+')
		if (ft_isalnum(key[i]) == false && key[i] != '_')
			return (false);
	if (key[i] == '+' && key[i + 1] != '=')
		return (false);
	return (true);
}

int	count_strs_in_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		++i;
	return (i);
}

char	*dup_in_lowercase(const char *str)
{
	char	*lower;
	int		i;

	lower = ft_strdup(str);
	if (lower == NULL)
		return (NULL);
	i = -1;
	while (lower[++i])
		lower[i] = ft_tolower(lower[i]);
	return (lower);
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
