/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:02:44 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 00:40:06 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "define.h"
#include "exec.h"
#include "libft.h"

int			redirect_failed(t_redir_list *node, int err);
static int	set_redir_in(t_redir_list *node, t_cmd_info *info);
static int	set_redir_out(t_redir_list *node, t_cmd_info *info);
static int	set_redir_append(t_redir_list *node, t_cmd_info *info);
static int	set_redir_heredoc(t_redir_list *node, t_cmd_info *info);

int	set_redirection(t_redir_list *node, t_cmd_info *info)
{
	if (node->data.type == R_IN)
		return (set_redir_in(node, info));
	else if (node->data.type == R_OUT)
		return (set_redir_out(node, info));
	else if (node->data.type == R_APPEND)
		return (set_redir_append(node, info));
	else if (node->data.type == R_HEREDOC)
		return (set_redir_heredoc(node, info));
	return (FATAL_ERROR);
}

static int	set_redir_in(t_redir_list *node, t_cmd_info *info)
{
	int	fd;

	fd = open(node->data.value.file_name, O_RDONLY);
	if (fd < 0)
		return (redirect_failed(node, errno));
	free(node->data.value.file_name);
	node->data.value.file_name = NULL;
	info->in = fd;
	return (NO_ERROR);
}

static int	set_redir_out(t_redir_list *node, t_cmd_info *info)
{
	int	fd;

	fd = open(node->data.value.file_name, \
		O_WRONLY | O_CREAT | O_TRUNC, PERM_MASK);
	if (fd < 0)
		return (redirect_failed(node, errno));
	free(node->data.value.file_name);
	node->data.value.file_name = NULL;
	info->out = fd;
	return (NO_ERROR);
}

static int	set_redir_append(t_redir_list *node, t_cmd_info *info)
{
	int	fd;

	fd = open(node->data.value.file_name, \
		O_WRONLY | O_CREAT | O_APPEND, PERM_MASK);
	if (fd < 0)
		return (redirect_failed(node, errno));
	free(node->data.value.file_name);
	node->data.value.file_name = NULL;
	info->out = fd;
	return (NO_ERROR);
}

static int	set_redir_heredoc(t_redir_list *node, t_cmd_info *info)
{
	info->in = node->data.value.heredoc.pipefd;
	return (NO_ERROR);
}
