/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 21:35:03 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/29 18:29:10 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "shell.h"
#include "exec.h"
#include "exec_util.h"
#include "define.h"
#include "libft.h"

static bool	is_n_string(const char *str);

int	exec_echo(char **argv)
{
	bool	n_option;

	argv++;
	n_option = false;
	while (*argv && is_n_string(*argv))
	{
		n_option = true;
		argv++;
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		if (argv[1])
			write(STDOUT_FILENO, " ", 1);
		argv++;
	}
	if (!n_option)
		write(STDOUT_FILENO, "\n", 1);
	return (NO_ERROR);
}

static bool	is_n_string(const char *str)
{
	if (ft_strncmp(str, "-n", 2) != 0)
		return (false);
	str += 2;
	while (*str == 'n')
		str++;
	if (*str == '\0')
		return (true);
	return (false);
}
