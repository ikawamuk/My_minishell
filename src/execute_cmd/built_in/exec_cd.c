/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 22:00:17 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 22:26:33 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "define.h"
#include "shell.h"
#include "exec_util.h"
#include "utils.h"
#include "libft.h"

static int	too_many_arg(void);
static int	home_not_set(void);
static int	error_cd(char *path);
static int	update_pwd_env(t_shell *shell, char *oldpwd);

int	exec_cd(char **argv, t_shell *shell)
{
	char			oldpwd[PATH_MAX];
	char			*to_directry;

	if (count_str_arr(argv) > 2)
		return (too_many_arg());
	if (!argv[1])
	{
		to_directry = ft_getenv(ENVNAME_HOME, shell->envp);
		if (!to_directry)
			return (home_not_set());
		if (!ft_strcmp(to_directry, ""))
			to_directry = ".";
	}
	else
		to_directry = argv[1];
	getcwd(oldpwd, PATH_MAX);
	if (chdir(to_directry) != 0)
		return (error_cd(to_directry));
	if (update_pwd_env(shell, oldpwd) == FATAL_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

static int	update_pwd_env(t_shell *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (update_env_var(shell, ENVNAME_OLDPWD, oldpwd) != NO_ERROR)
		return (FATAL_ERROR);
	if (update_env_var(shell, ENVNAME_PWD, cwd) != NO_ERROR)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

static int	error_cd(char *path)
{
	int	err;

	err = errno;
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(err), STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	home_not_set(void)
{
	ft_putstr_fd(CD_HOME_NOT_SET, STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	too_many_arg(void)
{
	ft_putstr_fd(CD_TOO_MANY_ARG, STDERR_FILENO);
	return (EXIT_FAILURE);
}
