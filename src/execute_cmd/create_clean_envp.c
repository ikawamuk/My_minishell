/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_clean_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:37:57 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/25 20:47:31 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "libft.h"

static size_t	count_new_arr_size(char **envp);
static char		**get_new_envp(char **new_envp, char **envp);

char	**create_clean_envp(char **envp)
{
	char	**new_envp;
	size_t	new_envp_size;

	new_envp_size = count_new_arr_size(envp);
	new_envp = ft_calloc(new_envp_size + 1, sizeof(char *));
	if (!new_envp)
		return (NULL);
	return (get_new_envp(new_envp, envp));
}

static char	**get_new_envp(char **new_envp, char **envp)
{
	size_t	i;
	size_t	new_i;

	i = 0;
	new_i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') != NULL)
		{
			new_envp[new_i] = ft_strdup(envp[i]);
			if (!new_envp[new_i])
			{
				free_str_arr(new_envp);
				return (NULL);
			}
			new_i++;
		}
		i++;
	}
	return (new_envp);
}

static size_t	count_new_arr_size(char **envp)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '=') != NULL)
			size++;
		i++;
	}
	return (size);
}
