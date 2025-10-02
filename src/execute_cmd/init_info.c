/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 13:20:07 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/27 13:20:10 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"
#include "exec.h"
#include "define.h"

int	init_cmd_info(t_cmd_info *info, t_shell *shell)
{
	info->in = STDIN_FILENO;
	info->out = STDOUT_FILENO;
	info->cmd_node = shell->cmd_list;
	shell->cmd_list = shell->cmd_list->next;
	info->cmd_node->next = NULL;
	info->paths_arr = NULL;
	info->cleaned_envp = NULL;
	info->cmd_path = NULL;
	return (NO_ERROR);
}
