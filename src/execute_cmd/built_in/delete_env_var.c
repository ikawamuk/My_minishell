/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 05:07:24 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 22:11:58 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "exec_util.h"
#include "utils.h"
#include "libft.h"

static char	**shrink_envp(char **envp, char *key);
static bool	find_env_var(char **envp, char *key);

int	delete_env_var(t_shell *shell, char *key)
{
	char	**tmp_arr;

	if (!find_env_var(shell->envp, key))
		return (NO_ERROR);
	tmp_arr = shrink_envp(shell->envp, key);
	if (!tmp_arr)
		return (FATAL_ERROR);
	free_str_arr(shell->envp);
	shell->envp = tmp_arr;
	return (NO_ERROR);
}

static char	**shrink_envp(char **envp, char *key)
{
	char	**result_arr;
	size_t	i;

	result_arr = ft_calloc(count_str_arr(envp), sizeof(char *));
	if (result_arr == NULL)
		return (NULL);
	i = 0;
	while (*envp)
	{
		if (!match_key(*envp, key, ft_strlen(key)))
		{
			result_arr[i] = ft_strdup(*envp);
			if (!result_arr[i])
			{
				free_str_arr(result_arr);
				return (NULL);
			}
			i++;
		}
		envp++;
	}
	return (result_arr);
}

static bool	find_env_var(char **envp, char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (*envp)
	{
		if (match_key(*envp, key, key_len))
			return (true);
		envp++;
	}
	return (false);
}
