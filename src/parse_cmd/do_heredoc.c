/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:41:30 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 20:50:03 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include "define.h"
#include "shell.h"
#include "utils.h"

static int	do_heredoc_loop(t_shell *shell);
int			gather_heredoc(t_redir *data, t_shell *shell);

int	do_heredoc(t_shell *shell)
{
	int	result;

	result = do_heredoc_loop(shell);
	if (result == FATAL_ERROR)
	{
		free_command_list(shell->cmd_list);
		free_str_arr(shell->envp);
		perror("minishell");
	}
	if (result == SIG_INTERRUPTED)
	{
		shell->last_status = 0x80 + SIGINT;
		free_command_list(shell->cmd_list);
		return (SIG_INTERRUPTED);
	}
	return (NO_ERROR);
}

static int	do_heredoc_loop(t_shell *shell)
{
	int				result;
	t_cmd_list		*cmd_list;
	t_redir_list	*redir_list;

	cmd_list = shell->cmd_list;
	while (cmd_list)
	{
		redir_list = shell->cmd_list->cmd.redir_list;
		while (redir_list)
		{
			if (redir_list->data.type == R_HEREDOC)
			{
				result = gather_heredoc(&redir_list->data, shell);
				if (result != NO_ERROR)
					return (result);
			}
			redir_list = redir_list->next;
		}
		cmd_list = cmd_list->next;
	}
	return (NO_ERROR);
}
