/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokurita <kokurita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:26:17 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 20:36:06 by kokurita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "shell.h"
#include "utils.h"
#include "libft.h"
#include "define.h"
#include "sig.h"

static void	fatal_error(t_shell *shell);
void		signal_handler(int sig);
int			event_hook(void);

void	set_signal_handler(t_shell *shell)
{
	struct sigaction	sa;
	struct sigaction	sa_ign;

	rl_event_hook = event_hook;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	ft_bzero(&sa_ign, sizeof(sa_ign));
	sa_ign.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) || sigaction(SIGQUIT, &sa_ign, NULL))
		fatal_error(shell);
	return ;
}

void	signal_handler(int sig)
{
	g_sig = sig;
}

static void	fatal_error(t_shell *shell)
{
	free_command_list(shell->cmd_list);
	free_str_arr(shell->envp);
	perror("minishell");
}

int	event_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
	}
	return (NO_ERROR);
}
