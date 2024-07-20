/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 13:28:29 by JFikents          #+#    #+#             */
/*   Updated: 2024/07/20 15:17:00 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_as_oldpwd(const char *pwd)
{
	char		*oldpwd;

	if (pwd == NULL)
		return (ft_printf_fd(2, ERROR_MSG_PERROR, "cd"), perror(NULL), 1);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (oldpwd == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "OLDPWD", E_ALLOC), EXIT_FAILURE);
	if (add_env_var(oldpwd) == EXIT_FAILURE)
		return (ft_printf_fd(2, ERROR_MSG, "cd", "Error setting OLDPWD", 2),
			free(oldpwd), EXIT_FAILURE);
	return (free(oldpwd), EXIT_SUCCESS);
}

static int	cd_oldpwd(void)
{
	int			status;
	const char	*oldpwd = getenv("OLDPWD");

	if (oldpwd == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "cd", "OLDPWD not set"), 1);
	status = chdir(oldpwd);
	return (status);
}

static int	set_new_pwd(void)
{
	const char	*pwd = getcwd(NULL, 0);
	char		*new_pwd;

	if (pwd == NULL)
		return (ft_printf_fd(2, ERROR_MSG_PERROR, "cd"), perror(NULL), 1);
	new_pwd = ft_strjoin("PWD=", pwd);
	ft_free_n_null((void **)&pwd);
	if (new_pwd == NULL)
		return (ft_printf_fd(2, ERROR_MSG, "PWD", E_ALLOC), EXIT_FAILURE);
	if (add_env_var(new_pwd) == EXIT_FAILURE)
		return (ft_printf_fd(2, ERROR_MSG, "cd", "Error setting PWD", 2),
			free(new_pwd), EXIT_FAILURE);
	return (free(new_pwd), EXIT_SUCCESS);
}

int	cd(const int argc, char **argv)
{
	const char	*pwd = getenv("PWD");
	int			status;

	status = 0;
	if (argc > 2)
		return (ft_printf_fd(2, ERROR_MSG, "cd", "too many arguments"),
			EXIT_FAILURE);
	if (argc == 1)
		status = chdir(getenv("HOME"));
	else if (ft_strncmp(argv[1], "-\0", 2) == 0)
		status = cd_oldpwd();
	else
		status = chdir(argv[1]);
	if (set_as_oldpwd(pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (status == -1)
	{
		ft_printf_fd(2, ERROR_MSG_PERROR"%s: ", "cd", argv[1]);
		perror(NULL);
		return (EXIT_FAILURE);
	}
	set_new_pwd();
	return (EXIT_SUCCESS);
}
