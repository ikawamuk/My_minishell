/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_trimed_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:33:38 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/02 20:29:59 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "utils.h"
#include "libft.h"

int			get_var_value(char *name, char **value_p, t_shell *shell);
int			safe_strdup(char *src, char **dst_p);
static bool	starts_with_home(char *pwd, char *home);
static int	replace_with_tilde(char *pwd, char *home, char **value_p);
static void	free_pwd_and_home(char *pwd, char *home);

int	get_trimed_pwd(char **value_p, t_shell *shell)
{
	int		result;
	char	*pwd;
	char	*home;

	pwd = NULL;
	home = NULL;
	if (get_var_value(ft_strdup(ENVNAME_PWD), &pwd, shell) != NO_ERROR)
		return (FATAL_ERROR);
	if (get_var_value(ft_strdup(ENVNAME_HOME), &home, shell) != NO_ERROR)
		return (FATAL_ERROR);
	if (!home | !pwd)
	{
		free_pwd_and_home(pwd, home);
		return (safe_strdup("", value_p));
	}
	if (starts_with_home(pwd, home))
	{
		result = replace_with_tilde(pwd, home, value_p);
		free_pwd_and_home(pwd, home);
		return (result);
	}
	result = safe_strdup(pwd, value_p);
	free_pwd_and_home(pwd, home);
	return (result);
}

static void	free_pwd_and_home(char *pwd, char *home)
{
	free(pwd);
	free(home);
}

static int	replace_with_tilde(char *pwd, char *home, char **value_p)
{
	size_t	len;
	size_t	home_len;
	char	*rest_path;

	home_len = ft_strlen(home);
	rest_path = pwd + home_len;
	if (*rest_path == '\0')
		return (safe_strdup("~", value_p));
	len = 2 + ft_strlen(rest_path);
	*value_p = ft_calloc(len + 1, sizeof(char));
	if (!*value_p)
		return (FATAL_ERROR);
	(*value_p)[0] = '~';
	(*value_p)[1] = '/';
	ft_strcpy(*value_p + 2, rest_path + 1);
	return (NO_ERROR);
}

static bool	starts_with_home(char *pwd, char *home)
{
	size_t	home_len;

	home_len = ft_strlen(home);
	if (ft_strncmp(pwd, home, home_len) != 0)
		return (false);
	if (pwd[home_len] == '\0' || pwd[home_len] == '/')
		return (true);
	return (false);
}
