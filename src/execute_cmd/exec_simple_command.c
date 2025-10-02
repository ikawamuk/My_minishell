/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simplecommand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:35:39 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/19 21:34:06 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "define.h"
#include "shell.h"
#include "exec.h"
#include "exec_util.h"
#include "utils.h"
#include "libft.h"

void	child_process(t_cmd_info *info, t_shell *shell);
int		create_child_process(t_cmd_info *info);
int		wait_child_process(pid_t pid);
int		exec_simple_built_in(t_cmd_info *info, t_shell *shell);
int		exec_null_cmd(t_cmd_info *info, t_shell *shell);

int	exec_simple_command(t_shell *shell)
{
	t_cmd_info	info;

	ft_bzero(&info, sizeof(info));
	info.out = STDOUT_FILENO;
	if (!shell->cmd_list->cmd.argv)
		return (exec_null_cmd(&info, shell));
	if (is_built_in(shell->cmd_list->cmd.argv[0]))
		return (exec_simple_built_in(&info, shell));
	if (create_child_process(&info) != NO_ERROR)
		return (FATAL_ERROR);
	if (info.pid == 0)
		child_process(&info, shell);
	shell->last_status = wait_child_process(info.pid);
	return (NO_ERROR);
}
