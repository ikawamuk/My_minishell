/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:00:21 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/27 12:37:47 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "exec.h"
#include "utils.h"

char		**create_clean_envp(char **envp);
char		**get_paths_arr(char **envp);
int			find_exec_file(t_cmd_info *info);
static void	exit_with_error(t_cmd_info *info, t_shell *shell, int status);

void	exec_external_command(t_cmd_info *info, t_shell *shell)
{
	int	result;

	info->cleaned_envp = create_clean_envp(shell->envp);
	if (!info->cleaned_envp)
		exit_with_error(info, shell, EXIT_FAILURE);
	info->paths_arr = get_paths_arr(shell->envp);
	if (!info->paths_arr)
		exit_with_error(info, shell, EXIT_FAILURE);
	result = find_exec_file(info);
	if (result == NO_ERROR)
		execve(info->cmd_path, info->cmd_node->cmd.argv, info->cleaned_envp);
	else
		exit_with_error(info, shell, result);
	exit_with_error(info, shell, EXIT_FAILURE);
	return ;
}

static void	exit_with_error(t_cmd_info *info, t_shell *shell, int status)
{
	info->cmd_node = free_command_list(info->cmd_node);
	info->cleaned_envp = free_str_arr(info->cleaned_envp);
	info->paths_arr = free_str_arr(info->paths_arr);
	free(info->cmd_path);
	info->cmd_path = NULL;
	shell->cmd_list = free_command_list(shell->cmd_list);
	shell->envp = free_str_arr(shell->envp);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(status);
}
