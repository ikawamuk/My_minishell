/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 05:00:54 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 22:29:09 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "shell.h"
#include "exec_util.h"

int	exec_unset(char **argv, t_shell *shell)
{
	argv++;
	while (*argv)
	{
		if (is_valid_key(*argv))
			if (delete_env_var(shell, *argv) == FATAL_ERROR)
				return (FATAL_ERROR);
		argv++;
	}
	return (NO_ERROR);
}
