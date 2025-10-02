/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_child_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:51:14 by kokurita          #+#    #+#             */
/*   Updated: 2025/09/29 21:48:30 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "sig.h"

static void	handle_child_sig(int status_loc);
size_t		count_pid_arr(pid_t *pid_arr);
int			get_status(int status);

int	wait_all_child_process(pid_t *pid_arr)
{
	int		status;
	int		status_loc;
	int		sig_flag;
	size_t	num;
	pid_t	last_pid;

	set_ignore_sighandler();
	status = EXIT_FAILURE;
	num = count_pid_arr(pid_arr);
	last_pid = pid_arr[num - 1];
	sig_flag = 0;
	while (*pid_arr)
	{
		if (waitpid(*pid_arr, &status_loc, 0) == last_pid)
			status = get_status(status_loc);
		if (!sig_flag && WIFSIGNALED(status_loc))
			sig_flag = WTERMSIG(status_loc);
		pid_arr++;
	}
	handle_child_sig(sig_flag);
	return (status);
}

static void	handle_child_sig(int sig_flag)
{
	if (sig_flag == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig_flag == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_sig = -1;
	return ;
}
