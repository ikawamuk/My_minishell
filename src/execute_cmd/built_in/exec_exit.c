/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 06:11:31 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/24 22:35:45 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "define.h"
#include "shell.h"
#include "utils.h"
#include "libft.h"

static bool	is_numeric(char *str);
static int	validate(int argc, char **argv);

int	exec_exit(char **argv, t_shell *shell)
{
	int		status;
	int		argc;

	argc = count_str_arr(argv);
	ft_putstr_fd(EXIT_MESSAGE, STDERR_FILENO);
	if (validate(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (argc == 1)
		status = shell->last_status;
	else
		status = ft_atoi(argv[1]);
	exit(status & 0xFF);
	return (NO_ERROR);
}

static int	validate(int argc, char **argv)
{
	if (argc == 1)
		return (NO_ERROR);
	if (!is_numeric(argv[1]))
	{
		ft_putstr_fd(EXIT_NOT_NUMERIC_ARG, STDERR_FILENO);
		exit(EXIT_SYNTAX_ERROR);
	}
	if (argc != 2)
	{
		ft_putstr_fd(EXIT_TOO_MANY_ARG, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (NO_ERROR);
}

static bool	is_numeric(char *str)
{
	if (ft_strlen(str) > 20)
		return (false);
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (false);
		str++;
	}
	return (true);
}
