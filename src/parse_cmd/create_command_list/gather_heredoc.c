/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:45:47 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 20:50:12 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "define.h"
#include "libft.h"
#include <signal.h>
#include "shell.h"
#include "utils.h"
#include "sig.h"

int			write_heredoc(char *eof, int write_fd, t_shell *shell);
static int	set_heredoc_readline(void);
void		signal_handler(int sig);
int			event_hook(void);

int	gather_heredoc(t_redir *data, t_shell *shell)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (FATAL_ERROR);
	set_heredoc_readline();
	data->value.heredoc.pipefd = pipefd[0];
	return (write_heredoc(data->value.heredoc.eof, pipefd[1], shell));
}

static int	set_heredoc_readline(void)
{
	struct sigaction	sa;

	rl_event_hook = event_hook;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL))
		return (FATAL_ERROR);
	return (NO_ERROR);
}
