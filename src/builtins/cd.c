/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/02 14:40:43 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_oldpwd(void)
{
	const char	*pwd = getcwd(NULL, 0);
	char		*oldpwd;

	if (pwd == NULL)
		return (ft_putstr_fd("minishell: cd: ", 2), perror(NULL), 1);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (oldpwd == NULL)
		return (free(pwd), ft_putstr_fd(E_ALLOC, 2), 1);
	ft_free_n_null((void **)&pwd);
	if (add_env_var(oldpwd) == NULL)
		return (ft_putstr_fd("minishell: cd: Error setting OLDPWD", 2),
			free(oldpwd), 1);
	return (free(oldpwd), 0);
}

static int	cd_oldpwd(void)
{
	int			status;
	const char	*oldpwd = getenv("OLDPWD");

	if (oldpwd == NULL)
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), 1);
	status = chdir(oldpwd);
	return (status);
}

void	cd(const int argc, char **argv)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	if (argc > 2)
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), (void)0);
	if (set_oldpwd() == 1)
		return ;
	if (argc == 1 || ft_strncmp(argv[1], "~\0", 2) == 0)
		status = chdir(getenv("HOME"));
	if (ft_strncmp(argv[1], "-\0", 2) == 0)
		status = cd_oldpwd();
	else
		status = chdir(argv[1]);
	if (status == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: ", argv[1]);
		perror(NULL);
	}
}
