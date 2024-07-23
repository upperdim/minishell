/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:16:14 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/23 17:27:23 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_key(const char *dollar_sign)
{
	const char	*key_start;
	char		*key;
	size_t		key_len;

	key_start = dollar_sign + 1;
	if (key_start[0] == '?')
		return (ft_strdup("LAST_PROCESS_EXIT_CODE"));
	key_len = 0;
	while (ft_isalnum((int)key_start[key_len]) || key_start[key_len] == '_')
		++key_len;
	if (key_len == 0)
		return ((void *)1);
	key = ft_substr(key_start, 0, key_len);
	return (key);
}

static int	expand_numbers(char *dollar_sign, char **expanded_line)
{
	char	*number_start;
	char	*line_after_numbers;
	char	*new_line;
	size_t	number_len;

	number_start = (char *)dollar_sign + 1;
	number_len = 0;
	while (ft_isdigit(number_start[number_len]))
		++number_len;
	line_after_numbers = ft_substr(number_start, number_len - 1,
			ft_strlen(number_start));
	if (line_after_numbers == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "heredoc", E_ALLOC), EXIT_FAILURE);
	dollar_sign[0] = '\0';
	new_line = ft_strjoin(*expanded_line, line_after_numbers);
	ft_free_n_null((void **)expanded_line);
	ft_free_n_null((void **)&line_after_numbers);
	if (new_line == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "heredoc", E_ALLOC), EXIT_FAILURE);
	*expanded_line = new_line;
	return (EXIT_SUCCESS);
}

static bool	is_question_mark(char *dollar_sign, char *env_key)
{
	const int	key_len = ft_strlen(env_key) + 1;

	if (dollar_sign[1] == '?')
	{
		if (ft_strncmp(env_key, "LAST_PROCESS_EXIT_CODE", key_len) == 0)
			return (true);
	}
	return (false);
}

static char	*replace_env_var(char *line, char *env_key)
{
	const char	*env_value = getenv(env_key);
	char		*dollar_sign;
	char		*new_line;
	char		*tmp_line;

	dollar_sign = ft_strchr(line, '$');
	while (dollar_sign != NULL && ft_strncmp(env_key, dollar_sign + 1,
			ft_strlen(env_key)) && !is_question_mark(dollar_sign, env_key))
		dollar_sign = ft_strchr(dollar_sign + 1, '$');
	dollar_sign[0] = '\0';
	new_line = ft_strjoin(line, env_value);
	if (is_question_mark(dollar_sign, env_key) == false)
		dollar_sign += ft_strlen(env_key) + 1;
	else
		dollar_sign += 2;
	ft_free_n_null((void **)&env_key);
	if (new_line == NULL)
		return (free(line), ft_printf_fd(2, ERROR_MSG, "heredoc", E_ALLOC),
			NULL);
	tmp_line = ft_strjoin(new_line, dollar_sign);
	ft_free_n_null((void **)&line);
	ft_free_n_null((void **)&new_line);
	if (tmp_line == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "heredoc", E_ALLOC), NULL);
	return (tmp_line);
}

char	*expand_heredoc(char *line)
{
	char	*new_line;
	char	*dollar_sign;
	char	*env_key;

	new_line = ft_strdup(line);
	if (new_line == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "heredoc", E_ALLOC), NULL);
	dollar_sign = ft_strchr(line, '$');
	while (dollar_sign != NULL && new_line != NULL)
	{
		env_key = (void *)1;
		if (ft_isdigit(dollar_sign[1]) == true)
		{
			if (expand_numbers(dollar_sign, &new_line) == EXIT_FAILURE)
				return (ft_free_n_null((void **)&new_line), NULL);
		}
		else
			env_key = extract_key(dollar_sign);
		if (env_key == NULL && ft_isdigit(dollar_sign[1]) == false)
			return (ft_printf_fd(2, ERR_MSG_MALLOC), free(new_line), NULL);
		if (env_key != (void *)1)
			new_line = replace_env_var(new_line, env_key);
		dollar_sign = ft_strchr(dollar_sign + 1, '$');
	}
	return (new_line);
}
