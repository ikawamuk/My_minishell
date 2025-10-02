/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:22:34 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/19 21:33:56 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "exec.h"
#include "utils.h"

int			exec_simple_command(t_shell *shell);
int			exec_multiple_command(t_shell *shell);
static void	fatal_error(t_shell *shell);

void	exec_command(t_shell *shell)
{
	if (shell->cmd_list->next == NULL)
	{
		if (exec_simple_command(shell) != NO_ERROR)
			fatal_error(shell);
	}
	else
		if (exec_multiple_command(shell) != NO_ERROR)
			fatal_error(shell);
	shell->cmd_list = free_command_list(shell->cmd_list);
	return ;
}

static void	fatal_error(t_shell *shell)
{
	shell->cmd_list = free_command_list(shell->cmd_list);
	shell->envp = free_str_arr(shell->envp);
	perror("minishell");
}
