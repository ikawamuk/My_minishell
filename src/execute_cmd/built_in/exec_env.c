/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 05:55:42 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 23:40:46 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "define.h"
#include "shell.h"
#include "libft.h"

int	error_env(void);

int	exec_env(char **argv, t_shell *shell)
{
	char		**envp;

	envp = shell->envp;
	if (argv[1])
		return (error_env());
	while (*envp)
	{
		if (ft_strchr(*envp, '=') != NULL)
			printf("%s\n", *envp);
		envp++;
	}
	return (NO_ERROR);
}

int	error_env(void)
{
	ft_putstr_fd(ENV_TOO_MANY_ARG, STDERR_FILENO);
	return (EXIT_FAILURE);
}
