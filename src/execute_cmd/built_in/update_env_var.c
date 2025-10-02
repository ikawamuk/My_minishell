/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:48:43 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 17:04:58 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "define.h"
#include "shell.h"
#include "exec_util.h"
#include "utils.h"

static int	set_env_var(char **env, char *key, char *value);
static int	append_env_var(t_shell *shell, char *key, char *value);
static char	**resize_str_arr(size_t arr_size, char **str_arr);

int	update_env_var(t_shell *shell, char *key, char *value)
{
	size_t	key_len;
	size_t	i;

	key_len = ft_strlen(key);
	i = 0;
	while (shell->envp[i])
	{
		if (match_key(shell->envp[i], key, key_len))
			return (set_env_var(&shell->envp[i], key, value));
		i++;
	}
	return (append_env_var(shell, key, value));
}

static int	set_env_var(char **env, char *key, char *value)
{
	char	*tmp;

	if (value == NULL)
		return (NO_ERROR);
	tmp = ft_strjoin_sep(key, value, "=");
	if (!tmp)
		return (FATAL_ERROR);
	free(*env);
	*env = tmp;
	return (NO_ERROR);
}

static int	append_env_var(t_shell *shell, char *key, char *value)
{
	size_t	new_size;
	char	**tmp_arr;

	new_size = count_str_arr(shell->envp) + 1;
	tmp_arr = resize_str_arr(new_size, shell->envp);
	if (tmp_arr == NULL)
		return (FATAL_ERROR);
	if (value == NULL)
		tmp_arr[new_size - 1] = ft_strdup(key);
	else
		tmp_arr[new_size - 1] = ft_strjoin_sep(key, value, "=");
	if (!tmp_arr[new_size - 1])
	{
		free_str_arr(tmp_arr);
		return (FATAL_ERROR);
	}
	free_str_arr(shell->envp);
	shell->envp = tmp_arr;
	return (NO_ERROR);
}

static char	**resize_str_arr(size_t new_size, char **str_arr)
{
	size_t	i;
	char	**result_arr;

	i = 0;
	result_arr = (char **)ft_calloc(new_size + 1, sizeof(char *));
	if (!result_arr)
		return (NULL);
	while (str_arr[i] && i < new_size)
	{
		result_arr[i] = ft_strdup(str_arr[i]);
		if (!result_arr[i])
		{
			free_str_arr(result_arr);
			return (NULL);
		}
		i++;
	}
	return (result_arr);
}
