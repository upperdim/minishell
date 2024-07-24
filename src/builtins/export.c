/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 15:18:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/24 20:11:46 by JFikents         ###   ########.fr       */
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

static char	*handle_plus_equals(char *arg)
{
	char		*plus_sign;
	char		*equal_sign;
	char		*value;
	char		*new_value;
	char		*new_arg;

	plus_sign = ft_strchr(arg, '+');
	equal_sign = ft_strchr(arg, '=');
	if (plus_sign == NULL || plus_sign[1] != '=' || equal_sign < plus_sign)
		return (arg);
	plus_sign[0] = '\0';
	value = getenv(arg);
	new_value = ft_strjoin(value, plus_sign + 2);
	if (new_value == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "export", E_ALLOC), NULL);
	plus_sign[0] = '=';
	plus_sign[1] = '\0';
	new_arg = ft_strjoin(arg, new_value);
	ft_free_n_null((void **)&new_value);
	ft_free_n_null((void **)&arg);
	if (new_arg == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "export", E_ALLOC), NULL);
	return (new_arg);
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
		{
			argv[i] = handle_plus_equals(argv[i]);
			if (argv[i] == NULL || add_env_var(argv[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (exit_status);
}
