/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 22:51:53 by kokurita          #+#    #+#             */
/*   Updated: 2025/09/27 13:22:24 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"
#include "define.h"
#include "exec.h"

int	create_pipe(t_cmd_info *info, int *next_pipe_read)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (FATAL_ERROR);
	info->in = *next_pipe_read;
	info->out = pipe_fd[1];
	*next_pipe_read = pipe_fd[0];
	return (NO_ERROR);
}
