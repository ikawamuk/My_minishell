/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 22:57:09 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/25 22:12:29 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <errno.h>
#include "define.h"
#include "exec.h"
#include "exec_util.h"
#include "libft.h"

static char	*get_command_path(t_cmd_info *info);
static int	command_not_found(t_cmd_info *info);
static int	check_command_path(char *path);
static int	error_with_message(char *path, char *message, int last_status);

int	find_exec_file(t_cmd_info *info)
{
	if (ft_strchr(info->cmd_node->cmd.argv[0], '/'))
	{
		info->cmd_path = ft_strdup(info->cmd_node->cmd.argv[0]);
		if (!info->cmd_path)
			return (FATAL_ERROR);
	}
	else
	{
		info->cmd_path = get_command_path(info);
		if (!info->cmd_path)
			return (FATAL_ERROR);
	}
	if (!*info->cmd_path)
		return (command_not_found(info));
	return (check_command_path(info->cmd_path));
}

static char	*get_command_path(t_cmd_info *info)
{
	char	*cmd;
	char	**dirs;
	char	*path;
	size_t	i;

	cmd = info->cmd_node->cmd.argv[0];
	dirs = info->paths_arr;
	i = 0;
	while (dirs[i])
	{
		path = ft_strjoin_sep(dirs[i], cmd, "/");
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (ft_calloc(1, sizeof(char)));
}

static int	check_command_path(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		if (errno == ENOENT)
			return (error_with_message(path, NO_SUCH_FILE_MESSAGE, \
				EXIT_FAILURE));
		else if (errno == EACCES)
			return (error_with_message(path, PERM_DENIED_MESSAGE, \
				EXIT_PERMISSION_DENIED));
		else
			return (FATAL_ERROR);
	}
	else if (S_ISDIR(st.st_mode))
		return (error_with_message(path, IS_A_DIR_MESSAGE, \
			EXIT_PERMISSION_DENIED));
	else if (access(path, X_OK) != 0)
		return (error_with_message(path, PERM_DENIED_MESSAGE, \
			EXIT_PERMISSION_DENIED));
	return (NO_ERROR);
}

static int	error_with_message(char *path, char *message, int last_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	return (last_status);
}

static int	command_not_found(t_cmd_info *info)
{
	ft_putstr_fd(info->cmd_node->cmd.argv[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(CMD_NOT_FOUND_MESSAGE, STDERR_FILENO);
	return (EXIT_COMMAND_NOT_FOUND);
}
