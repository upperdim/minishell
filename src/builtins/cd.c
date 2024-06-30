/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/06/30 13:31:42 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **argv)
{
	int	status;
	int	argc;
	int	i;

	status = 0;
	argc = 0;
	i = 0;
	while (argv[argc])
		argc++;
	if (argc > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), (void)0);
	//("OLDPWD", getcwd(NULL, 0));
	if (argc == 1 || ft_strncmp(argv[1], "~\0", 2) == 0)
		status = chdir(getenv("HOME"));
	if (ft_strncmp(argv[1], "-\0", 2) == 0)
		status = chdir(getenv("OLDPWD"));
	else
		status = chdir(argv[1]);
	if (status == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: ", argv[1]);
		perror(NULL);
	}
}
