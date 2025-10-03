/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 23:42:25 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/10/03 09:52:32 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "define.h"
#include "exec.h"
#include "libft.h"
#include "utils.h"
#include "sig.h"

int		get_status(int status);

int	wait_child_process(pid_t pid)
{
	int	status;
	int	status_loc;
	int	sig_flag;

	set_ignore_sighandler();
	status = EXIT_FAILURE;
	if (waitpid(-1, &status_loc, 0) == pid)
		status = get_status(status_loc);
	sig_flag = WTERMSIG(status_loc);
	if (sig_flag == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (sig_flag == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_sig = -1;
	return (status);
}

int	get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (0x80 + WTERMSIG(status));
	return (EXIT_FAILURE);
}
