/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 23:23:42 by kokurita          #+#    #+#             */
/*   Updated: 2025/09/27 13:22:08 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include "libft.h"
#include "define.h"

size_t			count_pid_arr(pid_t *pid_arr);
static void		cpy_pid_arr(pid_t *dest, pid_t *src);

int	append_pid(pid_t **pid_arr_p, pid_t pid)
{
	pid_t	*new_pid_arr;
	size_t	len;

	len = count_pid_arr(*pid_arr_p) + 1;
	new_pid_arr = (pid_t *)ft_calloc(sizeof(pid), len + 1);
	if (!new_pid_arr)
		return (FATAL_ERROR);
	cpy_pid_arr(new_pid_arr, *pid_arr_p);
	new_pid_arr[len - 1] = pid;
	free(*pid_arr_p);
	*pid_arr_p = new_pid_arr;
	return (NO_ERROR);
}

size_t	count_pid_arr(pid_t *pid_arr)
{
	size_t	count;

	count = 0;
	while (pid_arr && pid_arr[count])
		count++;
	return (count);
}

static void	cpy_pid_arr(pid_t *dest, pid_t *src)
{
	size_t	i;

	i = 0;
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return ;
}
