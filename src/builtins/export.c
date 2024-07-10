/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:18:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/08 20:32:00 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	**sort_env(void)
{
	const char	**env_var = (const char **)dup_environ();
	int			i;
	int			j;
	const char	*tmp;

	if (env_var == NULL)
		return (NULL);
	i = -1;
	while (env_var[++i])
	{
		j = i;
		while (env_var[++j])
		{
			if (ft_strncmp(env_var[i], env_var[j], ft_strlen(env_var[i])) > 0)
			{
				tmp = env_var[i];
				env_var[i] = env_var[j];
				env_var[j] = tmp;
			}
		}
	}
	return (env_var);
}

static int	print_env(void)
{
	const char	**p_environ = sort_env();
	int			i;
	char		*key;
	char		*equal_sign;
	int			key_len;

	if (p_environ == NULL)
		return (EXIT_FAILURE);
	i = -1;
	while (p_environ[++i])
	{
		equal_sign = ft_strchr((char *)p_environ[i], '=');
		key_len = ft_strlen(p_environ[i]);
		if (equal_sign != NULL)
			key_len = equal_sign - p_environ[i];
		key = ft_substr(p_environ[i], 0, key_len);
		if (equal_sign != NULL)
			ft_printf("declare -x %s=\"%s\"\n", key, getenv(key));
		else
			ft_printf("declare -x %s\n", p_environ[i]);
		ft_free_n_null((void **)&key);
	}
	ft_free_2d_array((void ***)&p_environ, FREE_ANY_SIZE);
	return (EXIT_SUCCESS);
}

int	is_key_valid(char *key)
{
	int	i;

	if (key == NULL || ft_isdigit(key[0]))
		return (0);
	i = -1;
	while (key[++i] != '\0' || key[i] == '=')
		if (ft_isalnum(key[i]) == false && key[i] != '_')
			return (false);
	return (true);
}

int	export(const int argc, char **argv)
{
	int		i;
	int		exit_status;

	if (argc == 1)
	{
		if (print_env() == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	i = 0;
	exit_status = EXIT_SUCCESS;
	while (argv[++i])
	{
		if (is_key_valid(argv[i]) == false)
		{
			ft_printf_fd(2, E_EXPORT, argv[i]);
			exit_status = EXIT_FAILURE;
		}
		else
			if (add_env_var(argv[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	return (exit_status);
}
