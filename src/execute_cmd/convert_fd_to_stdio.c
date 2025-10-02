/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_fd_to_stdio.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:23:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/27 13:25:02 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "define.h"
#include "exec.h"

int	convert_fd_to_stdio(t_cmd_info *info)
{
	if (dup2(info->in, STDIN_FILENO) == -1)
		return (FATAL_ERROR);
	if (info->in != STDIN_FILENO)
		close(info->in);
	if (dup2(info->out, STDOUT_FILENO) == -1)
		return (FATAL_ERROR);
	if (info->out != STDOUT_FILENO)
		close(info->out);
	return (NO_ERROR);
}

int	backup_stdio(int (*backup_fd_p)[2])
{
	(*backup_fd_p)[0] = dup(STDIN_FILENO);
	if ((*backup_fd_p)[0] == -1)
		return (FATAL_ERROR);
	(*backup_fd_p)[1] = dup(STDOUT_FILENO);
	if ((*backup_fd_p)[1] == -1)
	{
		close((*backup_fd_p)[0]);
		return (FATAL_ERROR);
	}
	return (NO_ERROR);
}

int	reverse_fd(int backup_fd[2])
{
	if (dup2(backup_fd[0], STDIN_FILENO) == -1)
		return (FATAL_ERROR);
	if (backup_fd[0] != STDIN_FILENO)
		close(backup_fd[0]);
	if (dup2(backup_fd[1], STDOUT_FILENO) == -1)
		return (FATAL_ERROR);
	if (backup_fd[1] != STDOUT_FILENO)
		close(backup_fd[1]);
	return (NO_ERROR);
}
