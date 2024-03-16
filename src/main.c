/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <JFikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 08:42:53 by tunsal            #+#    #+#             */
/*   Updated: 2024/03/16 21:23:26 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getuser(void)
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

char	*get_prompt(void)
{
	char	*temp;
	char	*prompt;
	char	*directory;

	temp = getcwd(NULL, 0);
	directory = ft_strrchr(temp, '/');
	directory = ft_strdup(directory + 1);
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(CYAN"1-A-1:", directory);
	ft_free_n_null((void **)&directory);
	directory = ft_strjoin(temp, BLUE" ");
	ft_free_n_null((void **)&temp);
	temp = ft_strjoin(directory, getuser());
	ft_free_n_null((void **)&directory);
	prompt = ft_strjoin(temp, "$ \x1b[0m");
	ft_free_n_null((void **)&temp);
	return (prompt);
}

void	control_c(int sig)
{
	(void)sig;
	return ;
}

int	main(void)
{
	t_mallocated		*mallocated;
	char				*tmp;
	char				*prompt;
	char				*line;
	struct sigaction	act;

	line = NULL;
	mallocated = NULL;
	act.sa_handler = control_c;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NODEFER;
	sigaction(SIGINT, &act, NULL);
	while (1)
	{
		ft_free_n_null((void **)&line);
		prompt = get_prompt();
		line = readline(prompt);
		ft_free_n_null((void **)&prompt);
		if (!line)
			break ;
		line = parse_line(line, mallocated);
		if (!line)
			continue ;
		if (ft_strnstr(line, "exit", 4))
			break ;
		if (ft_strnstr(line, "cd", 2))
		{
			if (line[2])
				chdir(line + 3);
			else
				chdir(getenv("HOME"));
		}
		if (ft_strnstr(line, "pwd", 3))
		{
			ft_printf("%s\n", tmp = getcwd(NULL, 0));
			ft_free_n_null((void **)&tmp);
		}
		if (ft_strnstr(line, "hi", 2))
			ft_printf("Hello\n");
	}
	ft_free_n_null((void **)&line);
	rl_clear_history();
	// system("leaks minishell");
	return (0);
}
