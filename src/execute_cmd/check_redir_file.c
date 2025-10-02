/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:32:39 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 00:40:23 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "redirection.h"
#include "define.h"
#include "libft.h"

static void	put_error_message(char *file, char *message);

int	redirect_failed(t_redir_list *node, int err)
{
	char	*message;

	if (err == ENOENT)
		message = NO_SUCH_FILE_MESSAGE;
	else if (err == EACCES)
		message = PERM_DENIED_MESSAGE;
	else if (err == EISDIR)
		message = IS_A_DIR_MESSAGE;
	else if (err == ENOTDIR)
		message = NO_SUCH_FILE_MESSAGE;
	else if (err == EROFS)
		message = PERM_DENIED_MESSAGE;
	else
		message = PERM_DENIED_MESSAGE;
	put_error_message(node->data.value.file_name, message);
	free(node->data.value.file_name);
	node->data.value.file_name = NULL;
	return (REDIRECT_FAILED);
}

static void	put_error_message(char *file, char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
}
