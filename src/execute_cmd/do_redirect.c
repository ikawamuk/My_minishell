/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:50:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 00:35:36 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include "define.h"
#include "shell.h"
#include "exec.h"
#include "libft.h"

int			redirect_expand(t_redir_list *list, t_shell *shell);
bool		is_ambiguous_redirect(t_redir_list *redir_list);
int			set_redir_loop(t_redir_list *list, t_cmd_info *info);
int			set_redirection(t_redir_list *node, t_cmd_info *info);
static int	ambiguous_redirect(void);
int			check_redir_file(t_redir redir);

int	do_redirection(t_cmd_info *info, t_shell *shell)
{
	int	result;

	if (redirect_expand(info->cmd_node->cmd.redir_list, shell) != NO_ERROR)
		return (FATAL_ERROR);
	if (is_ambiguous_redirect(info->cmd_node->cmd.redir_list))
		return (ambiguous_redirect());
	result = set_redir_loop(info->cmd_node->cmd.redir_list, info);
	if (result != NO_ERROR)
		return (result);
	return (NO_ERROR);
}

static int	ambiguous_redirect(void)
{
	ft_putstr_fd(AMBIG_REDIR_MESSAGE, STDERR_FILENO);
	return (REDIRECT_FAILED);
}

int	set_redir_loop(t_redir_list *list, t_cmd_info *info)
{
	int	result;

	while (list)
	{
		result = set_redirection(list, info);
		if (result != NO_ERROR)
			return (result);
		list = list->next;
	}
	return (NO_ERROR);
}
