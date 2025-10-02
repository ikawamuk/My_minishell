/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_built_in.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:50:23 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 20:16:29 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "define.h"
#include "shell.h"
#include "exec.h"
#include "utils.h"
#include "libft.h"

int			do_redirection(t_cmd_info *info, t_shell *shell);
int			exec_built_in(char **argv, t_shell *shell);
int			reverse_fd(int backup_fd[2]);
int			init_cmd_info(t_cmd_info *info, t_shell *shell);
static int	redirect_failed(t_cmd_info *info, t_shell *shell);
static int	fatal_error(t_cmd_info *info);
int			convert_fd_to_stdio(t_cmd_info *info);
int			backup_stdio(int (*backup_fd_p)[2]);

int	exec_simple_built_in(t_cmd_info *info, t_shell *shell)
{
	int	result;
	int	backup_fd[2];

	init_cmd_info(info, shell);
	if (backup_stdio(&backup_fd) != NO_ERROR)
		return (fatal_error(info));
	result = do_redirection(info, shell);
	if (result == FATAL_ERROR)
		return (fatal_error(info));
	if (result == REDIRECT_FAILED)
		return (redirect_failed(info, shell));
	if (convert_fd_to_stdio(info) != NO_ERROR)
		return (fatal_error(info));
	if (exec_built_in(info->cmd_node->cmd.argv, shell) != NO_ERROR)
		return (fatal_error(info));
	if (reverse_fd(backup_fd) == FATAL_ERROR)
		return (fatal_error(info));
	free_command_list(info->cmd_node);
	return (NO_ERROR);
}

int	exec_null_cmd(t_cmd_info *info, t_shell *shell)
{
	int	result;
	int	backup_fd[2];

	shell->last_status = EXIT_SUCCESS;
	init_cmd_info(info, shell);
	if (backup_stdio(&backup_fd) != NO_ERROR)
		return (fatal_error(info));
	result = do_redirection(info, shell);
	if (result == FATAL_ERROR)
		return (fatal_error(info));
	if (result == REDIRECT_FAILED)
		return (redirect_failed(info, shell));
	if (convert_fd_to_stdio(info) != NO_ERROR)
		return (fatal_error(info));
	if (reverse_fd(backup_fd) == FATAL_ERROR)
		return (fatal_error(info));
	info->cmd_node = free_command_list(info->cmd_node);
	return (NO_ERROR);
}

static int	fatal_error(t_cmd_info *info)
{
	info->cmd_node = free_command_list(info->cmd_node);
	return (FATAL_ERROR);
}

static int	redirect_failed(t_cmd_info *info, t_shell *shell)
{
	info->cmd_node = free_command_list(info->cmd_node);
	shell->last_status = EXIT_FAILURE;
	return (NO_ERROR);
}
