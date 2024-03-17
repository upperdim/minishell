/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 14:38:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/03/17 14:38:51 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getuser(void)
{
	char	*user;

	user = getenv("USER");
	if (!user)
	{
		user = getenv("LOGNAME");
		if (!user)
			return (NULL);
	}
	return (user);
}

char	*prompt(t_mallocated *to_free)
{
	char	*temp;
	char	*prompt;
	char	*directory;
	char	*input;

	temp = getcwd(NULL, 0);
	directory = ft_strrchr(temp, '/');
	ft_free_n_null((void **)&temp);
	directory = ft_strdup(directory + 1);
	temp = ft_strjoin(CYAN"1-A-1:", directory);
	ft_free_n_null((void **)&directory);
	directory = ft_strjoin(temp, BLUE" ");
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(directory, getuser());
	ft_free_n_null((void **)&directory);
	prompt = ft_strjoin(temp, "$ "WHITE);
	ft_free_n_null((void **)&temp);
	input = readline(prompt);
	ft_free_n_null((void **)&prompt);
	if (!input)
		errors((int [3]){EXIT, 0, 0}, NULL, to_free);
	return (input);
}
