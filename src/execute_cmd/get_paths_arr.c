/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:51:11 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/25 20:47:01 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "exec_util.h"
#include "utils.h"
#include "libft.h"

char	**get_paths_arr(char **envp)
{
	char	*path;
	char	**result;

	path = ft_getenv(ENVNAME_PATH, envp);
	if (!path || !*path)
	{
		result = (char **)ft_calloc(sizeof(char *), 2);
		if (!result)
			return (NULL);
		result[0] = ft_strdup(".");
		result[1] = NULL;
		return (result);
	}
	result = ft_split(path, ':');
	if (!result)
		return (NULL);
	return (result);
}
