/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 03:57:53 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 22:28:15 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "define.h"
#include "shell.h"
#include "exec_util.h"
#include "libft.h"

static int	print_export(t_shell *shell);
static void	get_key_and_value(char *env, char **key_p, char **value_p);

int	exec_export(char **argv, t_shell *shell)
{
	char	*value;
	char	*key;

	if (!++argv || !*argv)
		return (print_export(shell));
	while (*argv)
	{
		get_key_and_value(*argv, &key, &value);
		if (!is_valid_key(key))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		if (update_env_var(shell, key, value) == FATAL_ERROR)
			return (FATAL_ERROR);
		argv++;
	}
	return (NO_ERROR);
}

static void	get_key_and_value(char *env, char **key_p, char **value_p)
{
	*key_p = env;
	*value_p = ft_strchr(env, '=');
	if (*value_p != NULL)
	{
		**value_p = '\0';
		(*value_p)++;
	}
	return ;
}

static int	print_export(t_shell *shell)
{
	size_t	i;
	char	*key;
	char	*value;

	i = 0;
	while (shell->envp[i])
	{
		get_key_and_value(shell->envp[i], &key, &value);
		if (value)
		{
			printf("declare -x %s=\"%s\"\n", key, value);
			*(value - 1) = '=';
		}
		else
			printf("declare -x %s\n", key);
		i++;
	}
	return (NO_ERROR);
}
