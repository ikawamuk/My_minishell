/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 20:10:07 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 00:40:35 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include "shell.h"
#include "exec.h"
#include "define.h"
#include "utils.h"
#include "libft.h"

int			exec_built_in(char **argv, t_shell *shell);
int			exec_null_cmd(t_cmd_info *info, t_shell *shell);
void		exec_external_command(t_cmd_info *info, t_shell *shell);
int			init_cmd_info(t_cmd_info *info, t_shell *shell);
int			do_redirection(t_cmd_info *info, t_shell *shell);
bool		is_built_in(char *cmd);
int			convert_pipe_to_stdio(t_cmd_info *info);
static void	clean_child_process(t_cmd_info *info, t_shell *shell);
static void	exit_with_error(t_cmd_info *info, t_shell *shell);
static void	fatal_error(t_cmd_info *info, t_shell *shell);

void	child_process(t_cmd_info *info, t_shell *shell)
{
	int	result;

	set_default_sighandler();
	convert_pipe_to_stdio(info);
	init_cmd_info(info, shell);
	result = do_redirection(info, shell);
	if (result == FATAL_ERROR)
		fatal_error(info, shell);
	if (result == REDIRECT_FAILED)
		exit_with_error(info, shell);
	convert_pipe_to_stdio(info);
	if (!info->cmd_node->cmd.argv)
	{
		exec_null_cmd(info, shell);
		clean_child_process(info, shell);
		exit(shell->last_status);
	}
	if (is_built_in(info->cmd_node->cmd.argv[0]))
	{
		exec_built_in(info->cmd_node->cmd.argv, shell);
		clean_child_process(info, shell);
		exit(shell->last_status);
	}
	exec_external_command(info, shell);
}

int	convert_pipe_to_stdio(t_cmd_info *info)
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

static void	exit_with_error(t_cmd_info *info, t_shell *shell)
{
	clean_child_process(info, shell);
	exit(EXIT_FAILURE);
}

static void	fatal_error(t_cmd_info *info, t_shell *shell)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	clean_child_process(info, shell);
	exit(EXIT_FAILURE);
}

static void	clean_child_process(t_cmd_info *info, t_shell *shell)
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
}
