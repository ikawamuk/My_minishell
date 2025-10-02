/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 22:06:35 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/17 23:02:16 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "shell.h"
#include "utils.h"
#include "libft.h"

static int	get_special_parameter(char **value_p, int last_status);
static int	get_env_var_value(char *name, char **value_p, char **envp);

int	get_var_value(char *name, char **value_p, t_shell *shell)
{
	int	result;

	if (ft_strncmp(name, "?", 1) == 0)
		result = get_special_parameter(value_p, shell->last_status);
	else
		result = get_env_var_value(name, value_p, shell->envp);
	free(name);
	return (result);
}

static int	get_env_var_value(char *name, char **value_p, char **envp)
{
	*value_p = ft_getenv(name, envp);
	if (!*value_p)
		*value_p = "";
	*value_p = ft_strdup(*value_p);
	if (!*value_p)
		return (FATAL_ERROR);
	return (NO_ERROR);
}

static int	get_special_parameter(char **value_p, int last_status)
{
	*value_p = ft_itoa(last_status);
	if (!*value_p)
		return (FATAL_ERROR);
	return (NO_ERROR);
}
