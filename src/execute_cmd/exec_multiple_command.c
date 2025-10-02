/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:03:40 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 21:48:07 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "define.h"
#include "exec.h"
#include "utils.h"
#include "libft.h"
#include "sig.h"

int			create_child_process(t_cmd_info *info);
int			wait_all_child_process(pid_t *pid_arr);
void		child_process(t_cmd_info *info, t_shell *shell);
int			convert_pipe_to_stdio(t_cmd_info *info);
int			create_pipe(t_cmd_info *info, int *next_pipe_read);
int			append_pid(pid_t **pid_arr_p, pid_t pid);
size_t		count_pid_arr(pid_t *pid_arr);
int			get_status(int status);
static int	set_io_fd(t_cmd_info *info, t_shell *shell, int *next_pipe_read_p);
static int	update_infos(t_cmd_info *info, pid_t **pid_arr_p, t_shell *shell);
static void	init_infos(t_cmd_info *info, int *pipe_fd_p, pid_t **pid_arr_p);

int	exec_multiple_command(t_shell *shell)
{
	t_cmd_info	info;
	int			next_pipe_read;
	pid_t		*pid_arr;

	init_infos(&info, &next_pipe_read, &pid_arr);
	while (shell->cmd_list)
	{
		if (set_io_fd(&info, shell, &next_pipe_read) != NO_ERROR)
			return (FATAL_ERROR);
		if (create_child_process(&info) != NO_ERROR)
			return (FATAL_ERROR);
		if (info.pid == 0)
		{
			if (next_pipe_read != -1)
				close(next_pipe_read);
			child_process(&info, shell);
		}
		update_infos(&info, &pid_arr, shell);
	}
	shell->last_status = wait_all_child_process(pid_arr);
	free(pid_arr);
	return (NO_ERROR);
}

static void	init_infos(t_cmd_info *info, int *pipe_fd_p, pid_t **pid_arr_p)
{
	ft_bzero(info, sizeof(info));
	info->out = STDOUT_FILENO;
	*pid_arr_p = NULL;
	*pipe_fd_p = STDIN_FILENO;
}

static int	update_infos(t_cmd_info *info, pid_t **pid_arr_p, t_shell *shell)
{
	t_cmd_list	*next;

	if (info->in != STDIN_FILENO)
		close(info->in);
	if (info->out != STDOUT_FILENO)
		close(info->out);
	if (append_pid(pid_arr_p, info->pid) != NO_ERROR)
		return (FATAL_ERROR);
	free_command(shell->cmd_list->cmd);
	next = shell->cmd_list->next;
	free(shell->cmd_list);
	shell->cmd_list = next;
	return (NO_ERROR);
}

static int	set_io_fd(t_cmd_info *info, t_shell *shell, int *next_pipe_read_p)
{
	if (shell->cmd_list->next != NULL)
	{
		if (create_pipe(info, next_pipe_read_p) != NO_ERROR)
			return (FATAL_ERROR);
	}
	else
	{
		info->in = *next_pipe_read_p;
		info->out = STDOUT_FILENO;
		*next_pipe_read_p = -1;
	}
	return (NO_ERROR);
}
