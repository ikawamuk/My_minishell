/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:59:40 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 22:31:23 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "define.h"
#include "shell.h"
#include "exec_util.h"
#include "built_in.h"
#include "libft.h"

static int	exec_built_in_cmd(char **argv, t_shell *shell);

int	exec_built_in(char **argv, t_shell *shell)
{
	int	result;

	result = exec_built_in_cmd(argv, shell);
	if (result == FATAL_ERROR)
		return (FATAL_ERROR);
	shell->last_status = result;
	return (NO_ERROR);
}

static int	exec_built_in_cmd(char **argv, t_shell *shell)
{
	if (!ft_strcmp(argv[0], ECHO_CMD))
		return (exec_echo(argv));
	else if (!ft_strcmp(argv[0], CD_CMD))
		return (exec_cd(argv, shell));
	else if (!ft_strcmp(argv[0], PWD_CMD))
		return (exec_pwd());
	else if (!ft_strcmp(argv[0], EXPORT_CMD))
		return (exec_export(argv, shell));
	else if (!ft_strcmp(argv[0], UNSET_CMD))
		return (exec_unset(argv, shell));
	else if (!ft_strcmp(argv[0], ENVNAME_CMD))
		return (exec_env(argv, shell));
	else if (!ft_strcmp(argv[0], EXIT_CMD))
		return (exec_exit(argv, shell));
	return (FATAL_ERROR);
}

bool	is_built_in(char *cmd)
{
	if (!cmd || !*cmd)
		return (false);
	if (!ft_strcmp(cmd, ECHO_CMD))
		return (true);
	else if (!ft_strcmp(cmd, CD_CMD))
		return (true);
	else if (!ft_strcmp(cmd, PWD_CMD))
		return (true);
	else if (!ft_strcmp(cmd, EXIT_CMD))
		return (true);
	else if (!ft_strcmp(cmd, EXPORT_CMD))
		return (true);
	else if (!ft_strcmp(cmd, UNSET_CMD))
		return (true);
	else if (!ft_strcmp(cmd, ENVNAME_CMD))
		return (true);
	return (false);
}
